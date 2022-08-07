#include <string.h>

#include <lua/lua.h>

#include "lcode.h"
#include "ldebug.h"
#include "ldo.h"
#include "lfunc.h"
#include "llex.h"
#include "lmem.h"
#include "lobject.h"
#include "lopcodes.h"
#include "lparser.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"

#define hasmultret(k) ((k) == VCALL || (k) == VVARARG)

#define getlocvar(fs, i) ((fs)->f->locvars[(fs)->actvar[i]])

#define luaY_checklimit(fs, v, l, m)                                           \
    if ((v) > (l))                                                             \
    errorlimit(fs, l, m)

/*
** nodes for block list (list of active blocks)
*/
typedef struct BlockCnt {
    struct BlockCnt* previous; /* chain */
    int breaklist; /* list of jumps out of this loop */
    lu_byte nactvar; /* # active locals outside the breakable structure */
    lu_byte upval; /* true if some variable in the block is an upvalue */
    lu_byte isbreakable; /* true if `block' is a loop */
} BlockCnt;

/*
** prototypes for recursive non-terminal functions
*/
static void chunk(LexState* ls);
static void expr(LexState* ls, expdesc* v);

static void anchor_token(LexState* ls)
{
    if (ls->t.token == TK_NAME || ls->t.token == TK_STRING) {
        TString* ts = ls->t.seminfo.ts;
        luaX_newstring(ls, getstr(ts), ts->tsv.len);
    }
}

static void error_expected(LexState* ls, int token)
{
    luaX_syntaxerror(ls,
        luaO_pushfstring(ls->L, LUA_QS " expected", luaX_token2str(ls, token)));
}

static void errorlimit(FuncState* fs, int limit, const char* what)
{
    const char* msg = (fs->f->linedefined == 0)
        ? luaO_pushfstring(
            fs->L, "main function has more than %d %s", limit, what)
        : luaO_pushfstring(fs->L, "function at line %d has more than %d %s",
            fs->f->linedefined, limit, what);
    luaX_lexerror(fs->ls, msg, 0);
}

static int testnext(LexState* ls, int c)
{
    if (ls->t.token == c) {
        luaX_next(ls);
        return 1;
    } else
        return 0;
}

static void check(LexState* ls, int c)
{
    if (ls->t.token != c)
        error_expected(ls, c);
}

static void checknext(LexState* ls, int c)
{
    check(ls, c);
    luaX_next(ls);
}

#define check_condition(ls, c, msg)                                            \
    {                                                                          \
        if (!(c))                                                              \
            luaX_syntaxerror(ls, msg);                                         \
    }

static void check_match(LexState* ls, int what, int who, int where)
{
    if (!testnext(ls, what)) {
        if (where == ls->linenumber)
            error_expected(ls, what);
        else {
            luaX_syntaxerror(ls,
                luaO_pushfstring(ls->L,
                    LUA_QS " expected (to close " LUA_QS " at line %d)",
                    luaX_token2str(ls, what), luaX_token2str(ls, who), where));
        }
    }
}

static TString* str_checkname(LexState* ls)
{
    TString* ts;
    check(ls, TK_NAME);
    ts = ls->t.seminfo.ts;
    luaX_next(ls);
    return ts;
}

static void init_exp(expdesc* e, expkind k, int i)
{
    e->f = e->t = NO_JUMP;
    e->k = k;
    e->u.s.info = i;
}

static void codestring(LexState* ls, expdesc* e, TString* s)
{
    init_exp(e, VK, luaK_stringK(ls->fs, s));
}

static void checkname(LexState* ls, expdesc* e)
{
    codestring(ls, e, str_checkname(ls));
}

static int registerlocalvar(LexState* ls, TString* varname)
{
    FuncState* fs = ls->fs;
    Proto* f = fs->f;
    int oldsize = f->sizelocvars;
    luaM_growvector(ls->L, f->locvars, fs->nlocvars, f->sizelocvars, LocVar,
        SHRT_MAX, "too many local variables");
    while (oldsize < f->sizelocvars)
        f->locvars[oldsize++].varname = NULL;
    f->locvars[fs->nlocvars].varname = varname;
    luaC_objbarrier(ls->L, f, varname);
    return fs->nlocvars++;
}

#define new_localvarliteral(ls, v, n)                                          \
    new_localvar(                                                              \
        ls, luaX_newstring(ls, "" v, (sizeof(v) / sizeof(char)) - 1), n)

static void new_localvar(LexState* ls, TString* name, int n)
{
    FuncState* fs = ls->fs;
    luaY_checklimit(fs, fs->nactvar + n + 1, LUAI_MAXVARS, "local variables");
    fs->actvar[fs->nactvar + n]
        = cast(unsigned short, registerlocalvar(ls, name));
}

static void adjustlocalvars(LexState* ls, int nvars)
{
    FuncState* fs = ls->fs;
    fs->nactvar = cast_byte(fs->nactvar + nvars);
    for (; nvars; nvars--) {
        getlocvar(fs, fs->nactvar - nvars).startpc = fs->pc;
    }
}

static void removevars(LexState* ls, int tolevel)
{
    FuncState* fs = ls->fs;
    while (fs->nactvar > tolevel)
        getlocvar(fs, --fs->nactvar).endpc = fs->pc;
}

static void enterlevel(LexState* ls)
{
    if (++ls->L->nCcalls > LUAI_MAXCCALLS)
        luaX_lexerror(ls, "chunk has too many syntax levels", 0);
}

#define leavelevel(ls) ((ls)->L->nCcalls--)

static int block_follow(int token)
{
    switch (token) {
        case TK_ELSE:
        case TK_ELSEIF:
        case TK_END:
        case TK_UNTIL:
        case TK_EOS:
            return 1;
        default:
            return 0;
    }
}

static int cond(LexState* ls)
{
    // cond -> exp
    expdesc v;
    // read condition
    expr(ls, &v);
    if (v.k == VNIL)
        // `falses' are all equal here
        v.k = VFALSE;
    luaK_goiftrue(ls->fs, &v);
    return v.f;
}

static int test_then_block(LexState* ls)
{
    // test_then_block -> [IF | ELSEIF] cond THEN block
    int condexit;
    // skip IF or ELSEIF
    luaX_next(ls);
    condexit = cond(ls);
    checknext(ls, TK_THEN);
    // `then' part
    block(ls);
    return condexit;
}

static void ifstat(LexState* ls, int line)
{
    // ifstat -> IF cond THEN block {ELSEIF cond THEN block} [ELSE block] END
    FuncState* fs = ls->fs;
    int flist;
    int escapelist = NO_JUMP;
    flist = test_then_block(ls); /* IF cond THEN block */
    while (ls->t.token == TK_ELSEIF) {
        luaK_concat(fs, &escapelist, luaK_jump(fs));
        luaK_patchtohere(fs, flist);
        flist = test_then_block(ls); /* ELSEIF cond THEN block */
    }
    if (ls->t.token == TK_ELSE) {
        luaK_concat(fs, &escapelist, luaK_jump(fs));
        luaK_patchtohere(fs, flist);
        luaX_next(ls); /* skip ELSE (after patch, for correct line info) */
        block(ls); /* `else' part */
    } else
        luaK_concat(fs, &escapelist, flist);
    luaK_patchtohere(fs, escapelist);
    check_match(ls, TK_END, TK_IF, line);
}

static int statement(LexState* ls)
{
    int line = ls->linenumber; /* may be needed for error messages */
    switch (ls->t.token) {
        case TK_IF: { /* stat -> ifstat */
            ifstat(ls, line);
            return 0;
        }
        case TK_WHILE: { /* stat -> whilestat */
            whilestat(ls, line);
            return 0;
        }
        case TK_DO: { /* stat -> DO block END */
            luaX_next(ls); /* skip DO */
            block(ls);
            check_match(ls, TK_END, TK_DO, line);
            return 0;
        }
        case TK_FOR: { /* stat -> forstat */
            forstat(ls, line);
            return 0;
        }
        case TK_REPEAT: { /* stat -> repeatstat */
            repeatstat(ls, line);
            return 0;
        }
        case TK_FUNCTION: {
            funcstat(ls, line); /* stat -> funcstat */
            return 0;
        }
        case TK_LOCAL: { /* stat -> localstat */
            luaX_next(ls); /* skip LOCAL */
            if (testnext(ls, TK_FUNCTION)) /* local function? */
                localfunc(ls);
            else
                localstat(ls);
            return 0;
        }
        case TK_RETURN: { /* stat -> retstat */
            retstat(ls);
            return 1; /* must be last statement */
        }
        case TK_BREAK: { /* stat -> breakstat */
            luaX_next(ls); /* skip BREAK */
            breakstat(ls);
            return 1; /* must be last statement */
        }
        default: {
            exprstat(ls);
            return 0; /* to avoid warnings */
        }
    }
}

static void chunk(LexState* ls)
{
    /* chunk -> { stat [`;'] } */
    int islast = 0;
    enterlevel(ls);
    while (!islast && !block_follow(ls->t.token)) {
        islast = statement(ls);
        testnext(ls, ';');
        lua_assert(ls->fs->f->maxstacksize >= ls->fs->freereg
            && ls->fs->freereg >= ls->fs->nactvar);
        ls->fs->freereg = ls->fs->nactvar; /* free registers */
    }
    leavelevel(ls);
}

static void open_func(LexState* ls, FuncState* fs)
{
    lua_State* L = ls->L;
    Proto* f = luaF_newproto(L);
    fs->f = f;
    // linked list of funcstates
    fs->prev = ls->fs;
    fs->ls = ls;
    fs->L = L;
    ls->fs = fs;
    fs->pc = 0;
    fs->lasttarget = -1;
    fs->jpc = NO_JUMP;
    fs->freereg = 0;
    fs->nk = 0;
    fs->np = 0;
    fs->nlocvars = 0;
    fs->nactvar = 0;
    fs->bl = NULL;
    f->source = ls->source;
    // registers 0/1 are always valid
    f->maxstacksize = 2;
    fs->h = luaH_new(L, 0, 0);
    // anchor table of constants and prototype (to avoid being collected)
    sethvalue2s(L, L->top, fs->h);
    incr_top(L);
    setptvalue2s(L, L->top, f);
    incr_top(L);
}

static void close_func(LexState* ls)
{
    lua_State* L = ls->L;
    FuncState* fs = ls->fs;
    Proto* f = fs->f;
    removevars(ls, 0);
    // final return
    luaK_ret(fs, 0, 0);
    luaM_reallocvector(L, f->code, f->sizecode, fs->pc, Instruction);
    f->sizecode = fs->pc;
    luaM_reallocvector(L, f->lineinfo, f->sizelineinfo, fs->pc, int);
    f->sizelineinfo = fs->pc;
    luaM_reallocvector(L, f->k, f->sizek, fs->nk, TValue);
    f->sizek = fs->nk;
    luaM_reallocvector(L, f->p, f->sizep, fs->np, Proto*);
    f->sizep = fs->np;
    luaM_reallocvector(L, f->locvars, f->sizelocvars, fs->nlocvars, LocVar);
    f->sizelocvars = fs->nlocvars;
    luaM_reallocvector(L, f->upvalues, f->sizeupvalues, f->nups, TString*);
    f->sizeupvalues = f->nups;
    lua_assert(luaG_checkcode(f));
    lua_assert(fs->bl == NULL);
    ls->fs = fs->prev;
    // last token read was anchored in defunct function; must reanchor it
    if (fs)
        anchor_token(ls);
    // remove table and prototype from the stack
    L->top -= 2;
}

Proto* luaY_parser(lua_State* L, ZIO* z, Mbuffer* buff, const char* name)
{
    struct LexState lexstate;
    struct FuncState funcstate;
    lexstate.buff = buff;
    luaX_setinput(L, &lexstate, z, luaS_new(L, name));
    open_func(&lexstate, &funcstate);
    funcstate.f->is_vararg = VARARG_ISVARARG; /* main func. is always vararg */
    luaX_next(&lexstate); /* read first token */
    chunk(&lexstate);
    check(&lexstate, TK_EOS);
    close_func(&lexstate);
    lua_assert(funcstate.prev == NULL);
    lua_assert(funcstate.f->nups == 0);
    lua_assert(lexstate.fs == NULL);
    return funcstate.f;
}

static int searchvar(FuncState* fs, TString* n)
{
    int i;
    for (i = fs->nactvar - 1; i >= 0; i--) {
        if (n == getlocvar(fs, i).varname)
            return i;
    }
    return -1; /* not found */
}

static int indexupvalue(FuncState* fs, TString* name, expdesc* v)
{
    int i;
    Proto* f = fs->f;
    int oldsize = f->sizeupvalues;
    for (i = 0; i < f->nups; i++) {
        if (fs->upvalues[i].k == v->k && fs->upvalues[i].info == v->u.s.info) {
            lua_assert(f->upvalues[i] == name);
            return i;
        }
    }
    /* new one */
    luaY_checklimit(fs, f->nups + 1, LUAI_MAXUPVALUES, "upvalues");
    luaM_growvector(
        fs->L, f->upvalues, f->nups, f->sizeupvalues, TString*, MAX_INT, "");
    while (oldsize < f->sizeupvalues)
        f->upvalues[oldsize++] = NULL;
    f->upvalues[f->nups] = name;
    luaC_objbarrier(fs->L, f, name);
    lua_assert(v->k == VLOCAL || v->k == VUPVAL);
    fs->upvalues[f->nups].k = cast_byte(v->k);
    fs->upvalues[f->nups].info = cast_byte(v->u.s.info);
    return f->nups++;
}

static int singlevaraux(FuncState* fs, TString* n, expdesc* var, int base)
{
    if (fs == NULL) { /* no more levels? */
        init_exp(var, VGLOBAL, NO_REG); /* default is global variable */
        return VGLOBAL;
    } else {
        /* look up at current level */
        int v = searchvar(fs, n);
        if (v >= 0) {
            init_exp(var, VLOCAL, v);
            if (!base)
                markupval(fs, v); /* local will be used as an upval */
            return VLOCAL;
        } else { /* not found at current level; try upper one */
            if (singlevaraux(fs->prev, n, var, 0) == VGLOBAL)
                return VGLOBAL;
            // else was LOCAL or UPVAL
            var->u.s.info = indexupvalue(fs, n, var);
            var->k = VUPVAL; /* upvalue in this level */
            return VUPVAL;
        }
    }
}

static void singlevar(LexState* ls, expdesc* var)
{
    TString* varname = str_checkname(ls);
    FuncState* fs = ls->fs;
    if (singlevaraux(fs, varname, var, 1) == VGLOBAL)
        /* info points to global name */
        var->u.s.info = luaK_stringK(fs, varname);
}

static void prefixexp(LexState* ls, expdesc* v)
{
    /* prefixexp -> NAME | '(' expr ')' */
    switch (ls->t.token) {
        case '(': {
            int line = ls->linenumber;
            luaX_next(ls);
            expr(ls, v);
            check_match(ls, ')', '(', line);
            luaK_dischargevars(ls->fs, v);
            return;
        }
        case TK_NAME: {
            singlevar(ls, v);
            return;
        }
        default: {
            luaX_syntaxerror(ls, "unexpected symbol");
            return;
        }
    }
}

static void primaryexp(LexState* ls, expdesc* v)
{
    /* primaryexp ->
          prefixexp { `.' NAME | `[' exp `]' | `:' NAME funcargs | funcargs } */
    FuncState* fs = ls->fs;
    prefixexp(ls, v);
    for (;;) {
        switch (ls->t.token) {
            case '.': { /* field */
                field(ls, v);
                break;
            }
            case '[': { /* `[' exp1 `]' */
                expdesc key;
                luaK_exp2anyreg(fs, v);
                yindex(ls, &key);
                luaK_indexed(fs, v, &key);
                break;
            }
            case ':': { /* `:' NAME funcargs */
                expdesc key;
                luaX_next(ls);
                checkname(ls, &key);
                luaK_self(fs, v, &key);
                funcargs(ls, v);
                break;
            }
            case '(':
            case TK_STRING:
            case '{': { /* funcargs */
                luaK_exp2nextreg(fs, v);
                funcargs(ls, v);
                break;
            }
            default:
                return;
        }
    }
}

static void simpleexp(LexState* ls, expdesc* v)
{
    /* simpleexp -> NUMBER | STRING | NIL | true | false | ... |
                    constructor | FUNCTION body | primaryexp */
    switch (ls->t.token) {
        case TK_NUMBER: {
            init_exp(v, VKNUM, 0);
            v->u.nval = ls->t.seminfo.r;
            break;
        }
        case TK_STRING: {
            codestring(ls, v, ls->t.seminfo.ts);
            break;
        }
        case TK_NIL: {
            init_exp(v, VNIL, 0);
            break;
        }
        case TK_TRUE: {
            init_exp(v, VTRUE, 0);
            break;
        }
        case TK_FALSE: {
            init_exp(v, VFALSE, 0);
            break;
        }
        case TK_DOTS: { /* vararg */
            FuncState* fs = ls->fs;
            check_condition(ls, fs->f->is_vararg,
                "cannot use " LUA_QL("...") " outside a vararg function");
            fs->f->is_vararg &= ~VARARG_NEEDSARG; /* don't need 'arg' */
            init_exp(v, VVARARG, luaK_codeABC(fs, OP_VARARG, 0, 1, 0));
            break;
        }
        case '{': { /* constructor */
            constructor(ls, v);
            return;
        }
        case TK_FUNCTION: {
            luaX_next(ls);
            body(ls, v, 0, ls->linenumber);
            return;
        }
        default: {
            primaryexp(ls, v);
            return;
        }
    }
    luaX_next(ls);
}

static UnOpr getunopr(int op)
{
    switch (op) {
        case TK_NOT:
            return OPR_NOT;
        case '-':
            return OPR_MINUS;
        case '#':
            return OPR_LEN;
        default:
            return OPR_NOUNOPR;
    }
}

static BinOpr getbinopr(int op)
{
    switch (op) {
        case '+':
            return OPR_ADD;
        case '-':
            return OPR_SUB;
        case '*':
            return OPR_MUL;
        case '/':
            return OPR_DIV;
        case '%':
            return OPR_MOD;
        case '^':
            return OPR_POW;
        case TK_CONCAT:
            return OPR_CONCAT;
        case TK_NE:
            return OPR_NE;
        case TK_EQ:
            return OPR_EQ;
        case '<':
            return OPR_LT;
        case TK_LE:
            return OPR_LE;
        case '>':
            return OPR_GT;
        case TK_GE:
            return OPR_GE;
        case TK_AND:
            return OPR_AND;
        case TK_OR:
            return OPR_OR;
        default:
            return OPR_NOBINOPR;
    }
}

static const struct {
    // left priority for each binary operator
    lu_byte left;
    // right priority
    lu_byte right;
} priority[] = {
    /* ORDER OPR */
    // `+' `-' `/' `%'
    { 6, 6 }, { 6, 6 }, { 7, 7 }, { 7, 7 }, { 7, 7 },
    // power and concat (right associative)
    { 10, 9 }, { 5, 4 },
    // equality and inequality
    { 3, 3 }, { 3, 3 },
    // order
    { 3, 3 }, { 3, 3 }, { 3, 3 }, { 3, 3 },
    // logical (and/or)
    { 2, 2 }, { 1, 1 }
};

#define UNARY_PRIORITY 8 /* priority for unary operators */

/*
** subexpr -> (simpleexp | unop subexpr) { binop subexpr }
** where `binop' is any binary operator with a priority higher than `limit'
*/
static BinOpr subexpr(LexState* ls, expdesc* v, unsigned int limit)
{
    BinOpr op;
    UnOpr uop;
    enterlevel(ls);
    uop = getunopr(ls->t.token);
    if (uop != OPR_NOUNOPR) {
        luaX_next(ls);
        subexpr(ls, v, UNARY_PRIORITY);
        luaK_prefix(ls->fs, uop, v);
    } else {
        simpleexp(ls, v);
    }
    /* expand while operators have priorities higher than `limit' */
    op = getbinopr(ls->t.token);
    while (op != OPR_NOBINOPR && priority[op].left > limit) {
        expdesc v2;
        BinOpr nextop;
        luaX_next(ls);
        luaK_infix(ls->fs, op, v);
        /* read sub-expression with higher priority */
        nextop = subexpr(ls, &v2, priority[op].right);
        luaK_posfix(ls->fs, op, v, &v2);
        op = nextop;
    }
    leavelevel(ls);
    return op; /* return first untreated operator */
}

static void expr(LexState* ls, expdesc* v) { subexpr(ls, v, 0); }
