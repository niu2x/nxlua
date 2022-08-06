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
