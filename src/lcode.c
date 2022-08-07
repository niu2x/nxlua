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
