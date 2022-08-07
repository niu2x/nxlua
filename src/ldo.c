#include <setjmp.h>
#include <stdlib.h>
#include <string.h>

#include <lua/lua.h>

#include "ldebug.h"
#include "ldo.h"
#include "lfunc.h"
#include "lgc.h"
#include "lmem.h"
#include "lobject.h"
#include "lopcodes.h"
#include "lparser.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"
#include "ltm.h"
#include "lundump.h"
#include "lvm.h"
#include "lzio.h"

/*
** Call a function (C or Lua). The function to be called is at *func.
** The arguments are on the stack, right after the function.
** When returns, all the results are on the stack, starting at the original
** function position.
*/
void luaD_call(lua_State* L, StkId func, int nResults)
{
    if (++L->nCcalls >= LUAI_MAXCCALLS) {
        if (L->nCcalls == LUAI_MAXCCALLS)
            luaG_runerror(L, "C stack overflow");
        else if (L->nCcalls >= (LUAI_MAXCCALLS + (LUAI_MAXCCALLS >> 3)))
            luaD_throw(L, LUA_ERRERR); /* error while handing stack error */
    }
    if (luaD_precall(L, func, nResults) == PCRLUA) /* is a Lua function? */
        luaV_execute(L, 1); /* call it */
    L->nCcalls--;
    luaC_checkGC(L);
}

static StkId tryfuncTM(lua_State* L, StkId func)
{
    const TValue* tm = luaT_gettmbyobj(L, func, TM_CALL);
    StkId p;
    ptrdiff_t funcr = savestack(L, func);
    if (!ttisfunction(tm))
        luaG_typeerror(L, func, "call");
    /* Open a hole inside the stack at `func' */
    for (p = L->top; p > func; p--)
        setobjs2s(L, p, p - 1);
    incr_top(L);
    func = restorestack(L, funcr); /* previous call may change stack */
    setobj2s(L, func, tm); /* tag method is the new function to be called */
    return func;
}

static StkId adjust_varargs(lua_State* L, Proto* p, int actual)
{
    int i;
    int nfixargs = p->numparams;
    Table* htab = NULL;
    StkId base, fixed;
    for (; actual < nfixargs; ++actual)
        setnilvalue(L->top++);
    /* move fixed parameters to final position */
    fixed = L->top - actual; /* first fixed argument */
    base = L->top; /* final position of first argument */
    for (i = 0; i < nfixargs; i++) {
        setobjs2s(L, L->top++, fixed + i);
        setnilvalue(fixed + i);
    }
    /* add `arg' parameter */
    if (htab) {
        sethvalue(L, L->top++, htab);
        lua_assert(iswhite(obj2gco(htab)));
    }
    return base;
}

#define inc_ci(L)                                                              \
    ((L->ci == L->end_ci)                                                      \
            ? growCI(L)                                                        \
            : (condhardstacktests(luaD_reallocCI(L, L->size_ci)), ++L->ci))

int luaD_precall(lua_State* L, StkId func, int nresults)
{
    LClosure* cl;
    ptrdiff_t funcr;
    if (!ttisfunction(func)) /* `func' is not a function? */
        func = tryfuncTM(L, func); /* check the `function' tag method */
    funcr = savestack(L, func);
    cl = &clvalue(func)->l;
    L->ci->savedpc = L->savedpc;
    if (!cl->isC) { /* Lua function? prepare its call */
        CallInfo* ci;
        StkId st, base;
        Proto* p = cl->p;
        luaD_checkstack(L, p->maxstacksize);
        func = restorestack(L, funcr);
        if (!p->is_vararg) { /* no varargs? */
            base = func + 1;
            if (L->top > base + p->numparams)
                L->top = base + p->numparams;
        } else { /* vararg function */
            int nargs = cast_int(L->top - func) - 1;
            base = adjust_varargs(L, p, nargs);
            func = restorestack(
                L, funcr); /* previous call may change the stack */
        }
        ci = inc_ci(L); /* now `enter' new function */
        ci->func = func;
        L->base = ci->base = base;
        ci->top = L->base + p->maxstacksize;
        lua_assert(ci->top <= L->stack_last);
        L->savedpc = p->code; /* starting point */
        ci->tailcalls = 0;
        ci->nresults = nresults;
        for (st = L->top; st < ci->top; st++)
            setnilvalue(st);
        L->top = ci->top;
        if (L->hookmask & LUA_MASKCALL) {
            L->savedpc++; /* hooks assume 'pc' is already incremented */
            luaD_callhook(L, LUA_HOOKCALL, -1);
            L->savedpc--; /* correct 'pc' */
        }
        return PCRLUA;
    } else { /* if is a C function, call it */
        CallInfo* ci;
        int n;
        luaD_checkstack(L, LUA_MINSTACK); /* ensure minimum stack size */
        ci = inc_ci(L); /* now `enter' new function */
        ci->func = restorestack(L, funcr);
        L->base = ci->base = ci->func + 1;
        ci->top = L->top + LUA_MINSTACK;
        lua_assert(ci->top <= L->stack_last);
        ci->nresults = nresults;
        if (L->hookmask & LUA_MASKCALL)
            luaD_callhook(L, LUA_HOOKCALL, -1);
        lua_unlock(L);
        n = (*curr_func(L)->c.f)(L); /* do the actual call */
        lua_lock(L);
        if (n < 0) /* yielding? */
            return PCRYIELD;
        else {
            luaD_poscall(L, L->top - n);
            return PCRC;
        }
    }
}

int luaD_poscall(lua_State* L, StkId firstResult)
{
    StkId res;
    int wanted, i;
    CallInfo* ci;
    if (L->hookmask & LUA_MASKRET)
        firstResult = callrethooks(L, firstResult);
    ci = L->ci--;
    res = ci->func; /* res == final position of 1st result */
    wanted = ci->nresults;
    L->base = (ci - 1)->base; /* restore base */
    L->savedpc = (ci - 1)->savedpc; /* restore savedpc */
    /* move results to correct place */
    for (i = wanted; i != 0 && firstResult < L->top; i--)
        setobjs2s(L, res++, firstResult++);
    while (i-- > 0)
        setnilvalue(res++);
    L->top = res;
    return (wanted - LUA_MULTRET); /* 0 iff wanted == LUA_MULTRET */
}
