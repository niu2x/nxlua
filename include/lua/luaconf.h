/*
** $Id: luaconf.h,v 1.80 2006/01/27 13:54:39 roberto Exp roberto $
** Configuration file for Lua
** See Copyright Notice in lua.h
*/

#ifndef LCONFIG_H
#define LCONFIG_H

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <lua/api.h>
#include <math.h>

#define LUA_NUMBER  double
#define LUA_INTEGER ptrdiff_t

#define LUAI_UINT32   uint32_t
#define LUAI_INT32    int32_t
#define LUAI_MAXINT32 0x7FFFFFFF
#define LUAI_UMEM     size_t
#define LUAI_MEM      ptrdiff_t

#define LUAI_USER_ALIGNMENT_T                                                  \
    union {                                                                    \
        double u;                                                              \
        void* s;                                                               \
        long l;                                                                \
    }
#define LUAI_UACNUMBER double

#define LUA_IDSIZE 60

#define LUAI_MAXCALLS    20000
#define LUAI_MAXCSTACK   8000
#define LUAI_MAXCCALLS   200
#define LUAI_MAXVARS     200
#define LUAI_MAXUPVALUES 60
#define LUAL_BUFFERSIZE  1024

// #define LUAI_BITSINT 32

#define lua_assert(c) assert((c))

#define LUA_QL(x) "'" x "'"
#define LUA_QS    LUA_QL("%s")

#define luai_numadd(a, b) ((a) + (b))
#define luai_numsub(a, b) ((a) - (b))
#define luai_nummul(a, b) ((a) * (b))
#define luai_numdiv(a, b) ((a) / (b))
#define luai_nummod(a, b) ((a)-floor((a) / (b)) * (b))
#define luai_numpow(a, b) (pow(a, b))
#define luai_numunm(a)    (-(a))
#define luai_numeq(a, b)  ((a) == (b))
#define luai_numlt(a, b)  ((a) < (b))
#define luai_numle(a, b)  ((a) <= (b))
#define luai_numisnan(a)  (!luai_numeq((a), (a)))

#define lua_number2int(i, d)     ((i) = (int)(d))
#define lua_number2integer(i, d) ((i) = (lua_Integer)(d))

#define LUAI_MAXNUMBER2STR 32 /* 16 digits, sign, point, and \0 */

#define LUA_NUMBER_FMT       "%.14g"
#define lua_number2str(s, n) sprintf((s), LUA_NUMBER_FMT, (n))
#define lua_str2number(s, p) strtod((s), (p))

#endif
