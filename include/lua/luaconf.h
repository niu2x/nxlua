/*
** $Id: luaconf.h,v 1.80 2006/01/27 13:54:39 roberto Exp roberto $
** Configuration file for Lua
** See Copyright Notice in lua.h
*/

#ifndef LCONFIG_H
#define LCONFIG_H

#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include <lua/api.h>

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

#endif