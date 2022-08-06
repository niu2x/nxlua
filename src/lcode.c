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