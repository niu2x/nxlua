#include <stdlib.h>
#include <string.h>

#include <lua/lua.h>

#include "ldebug.h"
#include "ldo.h"
#include "lfunc.h"
#include "lgc.h"
#include "lobject.h"
#include "lopcodes.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"
#include "ltm.h"
#include "lvm.h"

/* limit for table tag-method chains (to avoid loops) */
#define MAXTAGLOOP 100

const TValue* luaV_tonumber(const TValue* obj, TValue* n)
{
    lua_Number num;
    if (ttisnumber(obj))
        return obj;
    if (ttisstring(obj) && luaO_str2d(svalue(obj), &num)) {
        setnvalue(n, num);
        return n;
    } else
        return NULL;
}

int luaV_tostring(lua_State* L, StkId obj)
{
    if (!ttisnumber(obj))
        return 0;
    else {
        char s[LUAI_MAXNUMBER2STR];
        lua_Number n = nvalue(obj);
        lua_number2str(s, n);
        setsvalue2s(L, obj, luaS_new(L, s));
        return 1;
    }
}

// static void callTMres(lua_State* L, StkId res, const TValue* f,
//     const TValue* p1, const TValue* p2)
// {
//     ptrdiff_t result = savestack(L, res);
//     setobj2s(L, L->top, f); /* push function */
//     setobj2s(L, L->top + 1, p1); /* 1st argument */
//     setobj2s(L, L->top + 2, p2); /* 2nd argument */
//     luaD_checkstack(L, 3);
//     L->top += 3;
//     luaD_call(L, L->top - 3, 1);
//     res = restorestack(L, result);
//     L->top--;
//     setobjs2s(L, res, L->top);
// }

static int call_orderTM(
    lua_State* L, const TValue* p1, const TValue* p2, TMS event)
{
    const TValue* tm1 = luaT_gettmbyobj(L, p1, event);
    const TValue* tm2;
    /* no metamethod? */
    if (ttisnil(tm1))
        return -1;
    tm2 = luaT_gettmbyobj(L, p2, event);
    if (!luaO_rawequalObj(tm1, tm2)) /* different metamethods? */
        return -1;
    callTMres(L, L->top, tm1, p1, p2);
    return !l_isfalse(L->top);
}

static int l_strcmp(const TString* ls, const TString* rs)
{
    const char* l = getstr(ls);
    size_t ll = ls->tsv.len;
    const char* r = getstr(rs);
    size_t lr = rs->tsv.len;
    for (;;) {
        int temp = strcoll(l, r);
        if (temp != 0)
            return temp;
        else { /* strings are equal up to a `\0' */
            size_t len = strlen(l); /* index of first `\0' in both strings */
            if (len == lr) /* r is finished? */
                return (len == ll) ? 0 : 1;
            else if (len == ll) /* l is finished? */
                return -1; /* l is smaller than r (because r is not finished) */
            /* both strings longer than `len'; go on comparing (after the `\0')
             */
            len++;
            l += len;
            ll -= len;
            r += len;
            lr -= len;
        }
    }
}

int luaV_lessthan(lua_State* L, const TValue* l, const TValue* r)
{
    int res;
    if (ttype(l) != ttype(r))
        return luaG_ordererror(L, l, r);
    else if (ttisnumber(l))
        return luai_numlt(nvalue(l), nvalue(r));
    else if (ttisstring(l))
        return l_strcmp(rawtsvalue(l), rawtsvalue(r)) < 0;
    else if ((res = call_orderTM(L, l, r, TM_LT)) != -1)
        return res;
    return luaG_ordererror(L, l, r);
}
