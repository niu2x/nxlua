#include <lua/lua.h>

#include "lcode.h"
#include "ldebug.h"
#include "ldo.h"
#include "lgc.h"
#include "llex.h"
#include "lmem.h"
#include "lobject.h"
#include "lopcodes.h"
#include "lparser.h"
#include "ltable.h"

static int isnumeral(expdesc* e)
{
    return (e->k == VKNUM && e->t == NO_JUMP && e->f == NO_JUMP);
}

static int addk(FuncState* fs, TValue* k, TValue* v)
{
    lua_State* L = fs->L;
    TValue* idx = luaH_set(L, fs->h, k);
    Proto* f = fs->f;
    int oldsize = f->sizek;
    if (ttisnumber(idx)) {
        lua_assert(luaO_rawequalObj(&fs->f->k[cast_int(nvalue(idx))], v));
        return cast_int(nvalue(idx));
    } else {
        // constant not found; create a new entry
        setnvalue(idx, cast_num(fs->nk));
        luaM_growvector(L, f->k, fs->nk, f->sizek, TValue, MAXARG_Bx,
            "constant table overflow");
        while (oldsize < f->sizek)
            setnilvalue(&f->k[oldsize++]);
        setobj(L, &f->k[fs->nk], v);
        luaC_barrier(L, f, v);
        return fs->nk++;
    }
}

static void freereg(FuncState* fs, int reg)
{
    if (!ISK(reg) && reg >= fs->nactvar) {
        fs->freereg--;
        lua_assert(reg == fs->freereg);
    }
}

static int getjump(FuncState* fs, int pc)
{
    int offset = GETARG_sBx(fs->f->code[pc]);
    if (offset == NO_JUMP) /* point to itself represents end of list */
        return NO_JUMP; /* end of list */
    else
        return (pc + 1) + offset; /* turn offset into absolute position */
}

static Instruction* getjumpcontrol(FuncState* fs, int pc)
{
    Instruction* pi = &fs->f->code[pc];
    if (pc >= 1 && testTMode(GET_OPCODE(*(pi - 1))))
        return pi - 1;
    else
        return pi;
}

static int patchtestreg(FuncState* fs, int node, int reg)
{
    Instruction* i = getjumpcontrol(fs, node);
    if (GET_OPCODE(*i) != OP_TESTSET)
        // cannot patch other instructions
        return 0;
    if (reg != NO_REG && reg != GETARG_B(*i))
        SETARG_A(*i, reg);
    else
        // no register to put value or register already has the value
        *i = CREATE_ABC(OP_TEST, GETARG_B(*i), 0, GETARG_C(*i));

    return 1;
}

static void patchlistaux(
    FuncState* fs, int list, int vtarget, int reg, int dtarget)
{
    while (list != NO_JUMP) {
        int next = getjump(fs, list);
        if (patchtestreg(fs, list, reg))
            fixjump(fs, list, vtarget);
        else
            fixjump(fs, list, dtarget); /* jump to default target */
        list = next;
    }
}

static void dischargejpc(FuncState* fs)
{
    patchlistaux(fs, fs->jpc, fs->pc, NO_REG, fs->pc);
    fs->jpc = NO_JUMP;
}

static int luaK_code(FuncState* fs, Instruction i, int line)
{
    Proto* f = fs->f;
    /* `pc' will change */
    dischargejpc(fs);
    /* put new instruction in code array */
    luaM_growvector(fs->L, f->code, fs->pc, f->sizecode, Instruction, MAX_INT,
        "code size overflow");
    f->code[fs->pc] = i;
    /* save corresponding line information */
    luaM_growvector(fs->L, f->lineinfo, fs->pc, f->sizelineinfo, int, MAX_INT,
        "code size overflow");
    f->lineinfo[fs->pc] = line;
    return fs->pc++;
}

int luaK_codeABC(FuncState* fs, OpCode o, int a, int b, int c)
{
    lua_assert(getOpMode(o) == iABC);
    lua_assert(getBMode(o) != OpArgN || b == 0);
    lua_assert(getCMode(o) != OpArgN || c == 0);
    return luaK_code(fs, CREATE_ABC(o, a, b, c), fs->ls->lastline);
}

int luaK_stringK(FuncState* fs, TString* s)
{
    TValue o;
    setsvalue(fs->L, &o, s);
    return addk(fs, &o, &o);
}

int luaK_numberK(FuncState* fs, lua_Number r)
{
    TValue o;
    setnvalue(&o, r);
    return addk(fs, &o, &o);
}

static int boolK(FuncState* fs, int b)
{
    TValue o;
    setbvalue(&o, b);
    return addk(fs, &o, &o);
}

static int nilK(FuncState* fs)
{
    TValue k, v;
    setnilvalue(&v);
    // cannot use nil as key; instead use table itself to represent nil
    sethvalue(fs->L, &k, fs->h);
    return addk(fs, &k, &v);
}

// void luaK_setreturns(FuncState* fs, expdesc* e, int nresults)
// {
//     if (e->k == VCALL) { /* expression is an open function call? */
//         SETARG_C(getcode(fs, e), nresults + 1);
//     } else if (e->k == VVARARG) {
//         SETARG_B(getcode(fs, e), nresults + 1);
//         SETARG_A(getcode(fs, e), fs->freereg);
//         luaK_reserveregs(fs, 1);
//     }
// }

void luaK_ret(FuncState* fs, int first, int nret)
{
    luaK_codeABC(fs, OP_RETURN, first, nret + 1, 0);
}

void luaK_prefix(FuncState* fs, UnOpr op, expdesc* e)
{
    expdesc e2;
    e2.t = e2.f = NO_JUMP;
    e2.k = VKNUM;
    e2.u.nval = 0;
    switch (op) {
        case OPR_MINUS: {
            if (!isnumeral(e))
                // cannot operate on non-numeric constants
                luaK_exp2anyreg(fs, e);
            codearith(fs, OP_UNM, e, &e2);
            break;
        }
        case OPR_NOT:
            codenot(fs, e);
            break;
        case OPR_LEN: {
            luaK_exp2anyreg(fs, e); /* cannot operate on constants */
            codearith(fs, OP_LEN, e, &e2);
            break;
        }
        default:
            lua_assert(0);
    }
}

static void freeexp(FuncState* fs, expdesc* e)
{
    if (e->k == VNONRELOC)
        freereg(fs, e->u.s.info);
}

void luaK_reserveregs(FuncState* fs, int n)
{
    luaK_checkstack(fs, n);
    fs->freereg += n;
}

void luaK_nil(FuncState* fs, int from, int n)
{
    Instruction* previous;
    // no jumps to current position?
    if (fs->pc > fs->lasttarget) {
        // function start?
        if (fs->pc == 0) {
            if (from >= fs->nactvar)
                // positions are already clean
                return;
        } else {
            previous = &fs->f->code[fs->pc - 1];
            if (GET_OPCODE(*previous) == OP_LOADNIL) {
                int pfrom = GETARG_A(*previous);
                int pto = GETARG_B(*previous);
                if (pfrom <= from && from <= pto + 1) { /* can connect both? */
                    if (from + n - 1 > pto)
                        SETARG_B(*previous, from + n - 1);
                    return;
                }
            }
        }
    }
    // else no optimization
    luaK_codeABC(fs, OP_LOADNIL, from, from + n - 1, 0);
}

int luaK_codeABx(FuncState* fs, OpCode o, int a, unsigned int bc)
{
    lua_assert(getOpMode(o) == iABx || getOpMode(o) == iAsBx);
    lua_assert(getCMode(o) == OpArgN);
    return luaK_code(fs, CREATE_ABx(o, a, bc), fs->ls->lastline);
}

static void discharge2reg(FuncState* fs, expdesc* e, int reg)
{
    luaK_dischargevars(fs, e);
    switch (e->k) {
        case VNIL: {
            luaK_nil(fs, reg, 1);
            break;
        }
        case VFALSE:
        case VTRUE: {
            luaK_codeABC(fs, OP_LOADBOOL, reg, e->k == VTRUE, 0);
            break;
        }
        case VK: {
            luaK_codeABx(fs, OP_LOADK, reg, e->u.s.info);
            break;
        }
        case VKNUM: {
            luaK_codeABx(fs, OP_LOADK, reg, luaK_numberK(fs, e->u.nval));
            break;
        }
        case VRELOCABLE: {
            Instruction* pc = &getcode(fs, e);
            SETARG_A(*pc, reg);
            break;
        }
        case VNONRELOC: {
            if (reg != e->u.s.info)
                luaK_codeABC(fs, OP_MOVE, reg, e->u.s.info, 0);
            break;
        }
        default: {
            lua_assert(e->k == VVOID || e->k == VJMP);
            return; /* nothing to do... */
        }
    }
    e->u.s.info = reg;
    e->k = VNONRELOC;
}

static void exp2reg(FuncState* fs, expdesc* e, int reg)
{
    discharge2reg(fs, e, reg);
    if (e->k == VJMP)
        luaK_concat(fs, &e->t, e->u.s.info); /* put this jump in `t' list */
    if (hasjumps(e)) {
        int final; /* position after whole expression */
        int p_f = NO_JUMP; /* position of an eventual LOAD false */
        int p_t = NO_JUMP; /* position of an eventual LOAD true */
        if (need_value(fs, e->t) || need_value(fs, e->f)) {
            int fj = (e->k == VJMP) ? NO_JUMP : luaK_jump(fs);
            p_f = code_label(fs, reg, 0, 1);
            p_t = code_label(fs, reg, 1, 0);
            luaK_patchtohere(fs, fj);
        }
        final = luaK_getlabel(fs);
        patchlistaux(fs, e->f, final, reg, p_f);
        patchlistaux(fs, e->t, final, reg, p_t);
    }
    e->f = e->t = NO_JUMP;
    e->u.s.info = reg;
    e->k = VNONRELOC;
}

void luaK_setlist(FuncState* fs, int base, int nelems, int tostore)
{
    int c = (nelems - 1) / LFIELDS_PER_FLUSH + 1;
    int b = (tostore == LUA_MULTRET) ? 0 : tostore;
    lua_assert(tostore != 0);
    if (c <= MAXARG_C)
        luaK_codeABC(fs, OP_SETLIST, base, b, c);
    else {
        luaK_codeABC(fs, OP_SETLIST, base, b, 0);
        luaK_code(fs, cast(Instruction, c), fs->ls->lastline);
    }
    fs->freereg = base + 1; /* free registers with list values */
}

void luaK_exp2nextreg(FuncState* fs, expdesc* e)
{
    luaK_dischargevars(fs, e);
    freeexp(fs, e);
    luaK_reserveregs(fs, 1);
    exp2reg(fs, e, fs->freereg - 1);
}

int luaK_exp2anyreg(FuncState* fs, expdesc* e)
{
    luaK_dischargevars(fs, e);
    if (e->k == VNONRELOC) {
        if (!hasjumps(e))
            /* exp is already in a register */
            return e->u.s.info;
        /* reg. is not a local? */
        if (e->u.s.info >= fs->nactvar) {
            /* put value on it */
            exp2reg(fs, e, e->u.s.info);
            return e->u.s.info;
        }
    }
    /* default */
    luaK_exp2nextreg(fs, e);
    return e->u.s.info;
}

void luaK_dischargevars(FuncState* fs, expdesc* e)
{
    switch (e->k) {
        case VLOCAL: {
            e->k = VNONRELOC;
            break;
        }
        case VUPVAL: {
            e->u.s.info = luaK_codeABC(fs, OP_GETUPVAL, 0, e->u.s.info, 0);
            e->k = VRELOCABLE;
            break;
        }
        case VGLOBAL: {
            e->u.s.info = luaK_codeABx(fs, OP_GETGLOBAL, 0, e->u.s.info);
            e->k = VRELOCABLE;
            break;
        }
        case VINDEXED: {
            freereg(fs, e->u.s.aux);
            freereg(fs, e->u.s.info);
            e->u.s.info
                = luaK_codeABC(fs, OP_GETTABLE, 0, e->u.s.info, e->u.s.aux);
            e->k = VRELOCABLE;
            break;
        }
        case VVARARG:
        case VCALL: {
            luaK_setoneret(fs, e);
            break;
        }
        default:
            // there is one value available (somewhere)
            break;
    }
}
