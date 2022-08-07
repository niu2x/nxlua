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
#define Protect(x)                                                             \
    {                                                                          \
        L->savedpc = pc;                                                       \
        {                                                                      \
            x;                                                                 \
        };                                                                     \
        base = L->base;                                                        \
    }

#define arith_op(op, tm)                                                       \
    {                                                                          \
        TValue* rb = RKB(i);                                                   \
        TValue* rc = RKC(i);                                                   \
        if (ttisnumber(rb) && ttisnumber(rc)) {                                \
            lua_Number nb = nvalue(rb), nc = nvalue(rc);                       \
            setnvalue(ra, op(nb, nc));                                         \
        } else                                                                 \
            Protect(Arith(L, ra, rb, rc, tm));                                 \
    }

#define RA(i) (base + GETARG_A(i))
/* to be used after possible stack reallocation */
#define RB(i) check_exp(getBMode(GET_OPCODE(i)) == OpArgR, base + GETARG_B(i))
#define RC(i) check_exp(getCMode(GET_OPCODE(i)) == OpArgR, base + GETARG_C(i))
#define RKB(i)                                                                 \
    check_exp(getBMode(GET_OPCODE(i)) == OpArgK,                               \
        ISK(GETARG_B(i)) ? k + INDEXK(GETARG_B(i)) : base + GETARG_B(i))
#define RKC(i)                                                                 \
    check_exp(getCMode(GET_OPCODE(i)) == OpArgK,                               \
        ISK(GETARG_C(i)) ? k + INDEXK(GETARG_C(i)) : base + GETARG_C(i))
#define KBx(i) check_exp(getBMode(GET_OPCODE(i)) == OpArgK, k + GETARG_Bx(i))

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
//

static void callTMres(lua_State* L, StkId res, const TValue* f,
    const TValue* p1, const TValue* p2)
{
    ptrdiff_t result = savestack(L, res);
    setobj2s(L, L->top, f); /* push function */
    setobj2s(L, L->top + 1, p1); /* 1st argument */
    setobj2s(L, L->top + 2, p2); /* 2nd argument */
    luaD_checkstack(L, 3);
    L->top += 3;
    luaD_call(L, L->top - 3, 1);
    res = restorestack(L, result);
    L->top--;
    setobjs2s(L, res, L->top);
}

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

void luaV_execute(lua_State* L, int nexeccalls)
{
    LClosure* cl;
    StkId base;
    TValue* k;
    const Instruction* pc;
reentry: /* entry point */
    lua_assert(isLua(L->ci));
    pc = L->savedpc;
    cl = &clvalue(L->ci->func)->l;
    base = L->base;
    k = cl->p->k;
    /* main loop of interpreter */
    for (;;) {
        const Instruction i = *pc++;
        StkId ra;
        if ((L->hookmask & (LUA_MASKLINE | LUA_MASKCOUNT))
            && (--L->hookcount == 0 || L->hookmask & LUA_MASKLINE)) {
            traceexec(L, pc);
            if (L->status == LUA_YIELD) { /* did hook yield? */
                L->savedpc = pc - 1;
                return;
            }
            base = L->base;
        }
        /* warning!! several calls may realloc the stack and invalidate `ra'
         */
        ra = RA(i);
        lua_assert(base == L->base && L->base == L->ci->base);
        lua_assert(base <= L->top && L->top <= L->stack + L->stacksize);
        lua_assert(L->top == L->ci->top || luaG_checkopenop(i));
        switch (GET_OPCODE(i)) {
            case OP_MOVE: {
                setobjs2s(L, ra, RB(i));
                continue;
            }
            case OP_LOADK: {
                setobj2s(L, ra, KBx(i));
                continue;
            }
            case OP_LOADBOOL: {
                setbvalue(ra, GETARG_B(i));
                if (GETARG_C(i))
                    pc++; /* skip next instruction (if C) */
                continue;
            }
            case OP_LOADNIL: {
                TValue* rb = RB(i);
                do {
                    setnilvalue(rb--);
                } while (rb >= ra);
                continue;
            }
            case OP_GETUPVAL: {
                int b = GETARG_B(i);
                setobj2s(L, ra, cl->upvals[b]->v);
                continue;
            }
            case OP_GETGLOBAL: {
                TValue g;
                TValue* rb = KBx(i);
                sethvalue(L, &g, cl->env);
                lua_assert(ttisstring(rb));
                Protect(luaV_gettable(L, &g, rb, ra));
                continue;
            }
            case OP_GETTABLE: {
                Protect(luaV_gettable(L, RB(i), RKC(i), ra));
                continue;
            }
            case OP_SETGLOBAL: {
                TValue g;
                sethvalue(L, &g, cl->env);
                lua_assert(ttisstring(KBx(i)));
                Protect(luaV_settable(L, &g, KBx(i), ra));
                continue;
            }
            case OP_SETUPVAL: {
                UpVal* uv = cl->upvals[GETARG_B(i)];
                setobj(L, uv->v, ra);
                luaC_barrier(L, uv, ra);
                continue;
            }
            case OP_SETTABLE: {
                Protect(luaV_settable(L, ra, RKB(i), RKC(i)));
                continue;
            }
            case OP_NEWTABLE: {
                int b = GETARG_B(i);
                int c = GETARG_C(i);
                sethvalue(L, ra, luaH_new(L, luaO_fb2int(b), luaO_fb2int(c)));
                Protect(luaC_checkGC(L));
                continue;
            }
            case OP_SELF: {
                StkId rb = RB(i);
                setobjs2s(L, ra + 1, rb);
                Protect(luaV_gettable(L, rb, RKC(i), ra));
                continue;
            }
            case OP_ADD: {
                arith_op(luai_numadd, TM_ADD);
                continue;
            }
            case OP_SUB: {
                arith_op(luai_numsub, TM_SUB);
                continue;
            }
            case OP_MUL: {
                arith_op(luai_nummul, TM_MUL);
                continue;
            }
            case OP_DIV: {
                arith_op(luai_numdiv, TM_DIV);
                continue;
            }
            case OP_MOD: {
                arith_op(luai_nummod, TM_MOD);
                continue;
            }
            case OP_POW: {
                arith_op(luai_numpow, TM_POW);
                continue;
            }
            case OP_UNM: {
                TValue* rb = RB(i);
                if (ttisnumber(rb)) {
                    lua_Number nb = nvalue(rb);
                    setnvalue(ra, luai_numunm(nb));
                } else {
                    Protect(Arith(L, ra, rb, rb, TM_UNM));
                }
                continue;
            }
            case OP_NOT: {
                int res = l_isfalse(
                    RB(i)); /* next assignment may change this value */
                setbvalue(ra, res);
                continue;
            }
            case OP_LEN: {
                const TValue* rb = RB(i);
                switch (ttype(rb)) {
                    case LUA_TTABLE: {
                        setnvalue(ra, cast_num(luaH_getn(hvalue(rb))));
                        break;
                    }
                    case LUA_TSTRING: {
                        setnvalue(ra, cast_num(tsvalue(rb)->len));
                        break;
                    }
                    default: { /* try metamethod */
                        Protect(
                            if (!call_binTM(L, rb, luaO_nilobject, ra, TM_LEN))
                                luaG_typeerror(L, rb, "get length of");)
                    }
                }
                continue;
            }
            case OP_CONCAT: {
                int b = GETARG_B(i);
                int c = GETARG_C(i);
                Protect(luaV_concat(L, c - b + 1, c); luaC_checkGC(L));
                setobjs2s(L, RA(i), base + b);
                continue;
            }
            case OP_JMP: {
                dojump(L, pc, GETARG_sBx(i));
                continue;
            }
            case OP_EQ: {
                TValue* rb = RKB(i);
                TValue* rc = RKC(i);
                Protect(if (equalobj(L, rb, rc) == GETARG_A(i))
                            dojump(L, pc, GETARG_sBx(*pc));) pc++;
                continue;
            }
            case OP_LT: {
                Protect(if (luaV_lessthan(L, RKB(i), RKC(i)) == GETARG_A(i))
                            dojump(L, pc, GETARG_sBx(*pc));) pc++;
                continue;
            }
            case OP_LE: {
                Protect(if (lessequal(L, RKB(i), RKC(i)) == GETARG_A(i))
                            dojump(L, pc, GETARG_sBx(*pc));) pc++;
                continue;
            }
            case OP_TEST: {
                if (l_isfalse(ra) != GETARG_C(i))
                    dojump(L, pc, GETARG_sBx(*pc));
                pc++;
                continue;
            }
            case OP_TESTSET: {
                TValue* rb = RB(i);
                if (l_isfalse(rb) != GETARG_C(i)) {
                    setobjs2s(L, ra, rb);
                    dojump(L, pc, GETARG_sBx(*pc));
                }
                pc++;
                continue;
            }
            case OP_CALL: {
                int b = GETARG_B(i);
                int nresults = GETARG_C(i) - 1;
                if (b != 0)
                    L->top = ra + b; /* else previous instruction set top */
                L->savedpc = pc;
                switch (luaD_precall(L, ra, nresults)) {
                    case PCRLUA: {
                        nexeccalls++;
                        goto reentry; /* restart luaV_execute over new Lua
                                         function */
                    }
                    case PCRC: {
                        /* it was a C function (`precall' called it); adjust
                         * results */
                        if (nresults >= 0)
                            L->top = L->ci->top;
                        base = L->base;
                        continue;
                    }
                    default: {
                        return; /* yield */
                    }
                }
            }
            case OP_TAILCALL: {
                int b = GETARG_B(i);
                if (b != 0)
                    L->top = ra + b; /* else previous instruction set top */
                L->savedpc = pc;
                lua_assert(GETARG_C(i) - 1 == LUA_MULTRET);
                switch (luaD_precall(L, ra, LUA_MULTRET)) {
                    case PCRLUA: {
                        /* tail call: put new frame in place of previous one
                         */
                        CallInfo* ci = L->ci - 1; /* previous frame */
                        int aux;
                        StkId func = ci->func;
                        StkId pfunc
                            = (ci + 1)->func; /* previous function index */
                        if (L->openupval)
                            luaF_close(L, ci->base);
                        L->base = ci->base
                            = ci->func + ((ci + 1)->base - pfunc);
                        for (aux = 0; pfunc + aux < L->top;
                             aux++) /* move frame down */
                            setobjs2s(L, func + aux, pfunc + aux);
                        ci->top = L->top = func + aux; /* correct top */
                        lua_assert(L->top
                            == L->base + clvalue(func)->l.p->maxstacksize);
                        ci->savedpc = L->savedpc;
                        ci->tailcalls++; /* one more call lost */
                        L->ci--; /* remove new frame */
                        goto reentry;
                    }
                    case PCRC: { /* it was a C function (`precall' called it)
                                  */
                        base = L->base;
                        continue;
                    }
                    default: {
                        return; /* yield */
                    }
                }
            }
            case OP_RETURN: {
                int b = GETARG_B(i);
                if (b != 0)
                    L->top = ra + b - 1;
                if (L->openupval)
                    luaF_close(L, base);
                L->savedpc = pc;
                b = luaD_poscall(L, ra);
                if (--nexeccalls
                    == 0) /* was previous function running `here'? */
                    return; /* no: return */
                else { /* yes: continue its execution */
                    if (b)
                        L->top = L->ci->top;
                    lua_assert(isLua(L->ci));
                    lua_assert(GET_OPCODE(*((L->ci)->savedpc - 1)) == OP_CALL);
                    goto reentry;
                }
            }
            case OP_FORLOOP: {
                lua_Number step = nvalue(ra + 2);
                lua_Number idx
                    = luai_numadd(nvalue(ra), step); /* increment index */
                lua_Number limit = nvalue(ra + 1);
                if (luai_numlt(0, step) ? luai_numle(idx, limit)
                                        : luai_numle(limit, idx)) {
                    dojump(L, pc, GETARG_sBx(i)); /* jump back */
                    setnvalue(ra, idx); /* update internal index... */
                    setnvalue(ra + 3, idx); /* ...and external index */
                }
                continue;
            }
            case OP_FORPREP: {
                const TValue* init = ra;
                const TValue* plimit = ra + 1;
                const TValue* pstep = ra + 2;
                L->savedpc = pc; /* next steps may throw errors */
                if (!tonumber(init, ra))
                    luaG_runerror(
                        L, LUA_QL("for") " initial value must be a number");
                else if (!tonumber(plimit, ra + 1))
                    luaG_runerror(L, LUA_QL("for") " limit must be a number");
                else if (!tonumber(pstep, ra + 2))
                    luaG_runerror(L, LUA_QL("for") " step must be a number");
                setnvalue(ra, luai_numsub(nvalue(ra), nvalue(pstep)));
                dojump(L, pc, GETARG_sBx(i));
                continue;
            }
            case OP_TFORLOOP: {
                StkId cb = ra + 3; /* call base */
                setobjs2s(L, cb + 2, ra + 2);
                setobjs2s(L, cb + 1, ra + 1);
                setobjs2s(L, cb, ra);
                L->top = cb + 3; /* func. + 2 args (state and index) */
                Protect(luaD_call(L, cb, GETARG_C(i)));
                L->top = L->ci->top;
                cb = RA(i) + 3; /* previous call may change the stack */
                if (!ttisnil(cb)) { /* continue loop? */
                    setobjs2s(L, cb - 1, cb); /* save control variable */
                    dojump(L, pc, GETARG_sBx(*pc)); /* jump back */
                }
                pc++;
                continue;
            }
            case OP_SETLIST: {
                int n = GETARG_B(i);
                int c = GETARG_C(i);
                int last;
                Table* h;
                if (n == 0) {
                    n = cast_int(L->top - ra) - 1;
                    L->top = L->ci->top;
                }
                if (c == 0)
                    c = cast_int(*pc++);
                runtime_check(L, ttistable(ra));
                h = hvalue(ra);
                last = ((c - 1) * LFIELDS_PER_FLUSH) + n;
                if (last > h->sizearray) /* needs more space? */
                    luaH_resizearray(L, h, last); /* pre-alloc it at once */
                for (; n > 0; n--) {
                    TValue* val = ra + n;
                    setobj2t(L, luaH_setnum(L, h, last--), val);
                    luaC_barriert(L, h, val);
                }
                continue;
            }
            case OP_CLOSE: {
                luaF_close(L, ra);
                continue;
            }
            case OP_CLOSURE: {
                Proto* p;
                Closure* ncl;
                int nup, j;
                p = cl->p->p[GETARG_Bx(i)];
                nup = p->nups;
                ncl = luaF_newLclosure(L, nup, cl->env);
                ncl->l.p = p;
                for (j = 0; j < nup; j++, pc++) {
                    if (GET_OPCODE(*pc) == OP_GETUPVAL)
                        ncl->l.upvals[j] = cl->upvals[GETARG_B(*pc)];
                    else {
                        lua_assert(GET_OPCODE(*pc) == OP_MOVE);
                        ncl->l.upvals[j]
                            = luaF_findupval(L, base + GETARG_B(*pc));
                    }
                }
                setclvalue(L, ra, ncl);
                Protect(luaC_checkGC(L));
                continue;
            }
            case OP_VARARG: {
                int b = GETARG_B(i) - 1;
                int j;
                CallInfo* ci = L->ci;
                int n = cast_int(ci->base - ci->func) - cl->p->numparams - 1;
                if (b == LUA_MULTRET) {
                    Protect(luaD_checkstack(L, n));
                    ra = RA(i); /* previous call may change the stack */
                    b = n;
                    L->top = ra + n;
                }
                for (j = 0; j < b; j++) {
                    if (j < n) {
                        setobjs2s(L, ra + j, ci->base - n + j);
                    } else {
                        setnilvalue(ra + j);
                    }
                }
                continue;
            }
        }
    }
}

void luaV_gettable(lua_State* L, const TValue* t, TValue* key, StkId val)
{
    int loop;
    for (loop = 0; loop < MAXTAGLOOP; loop++) {
        const TValue* tm;
        if (ttistable(t)) { /* `t' is a table? */
            Table* h = hvalue(t);
            const TValue* res = luaH_get(h, key); /* do a primitive get */
            if (!ttisnil(res) || /* result is no nil? */
                (tm = fasttm(L, h->metatable, TM_INDEX))
                    == NULL) { /* or no TM? */
                setobj2s(L, val, res);
                return;
            }
            /* else will try the tag method */
        } else if (ttisnil(tm = luaT_gettmbyobj(L, t, TM_INDEX)))
            luaG_typeerror(L, t, "index");
        if (ttisfunction(tm)) {
            callTMres(L, val, tm, t, key);
            return;
        }
        t = tm; /* else repeat with `tm' */
    }
    luaG_runerror(L, "loop in gettable");
}
