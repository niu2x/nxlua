/*
** $Id: lundump.h,v 1.39 2005/11/01 17:04:55 lhf Exp lhf $
** load precompiled Lua chunks
** See Copyright Notice in lua.h
*/

#ifndef LUNDUMP_H
#define LUNDUMP_H

#include "lobject.h"
#include "lzio.h"

/* load one chunk; from lundump.c */
Proto* luaU_undump(lua_State* L, ZIO* Z, Mbuffer* buff, const char* name);

/* make header; from lundump.c */
void luaU_header(char* h);

/* dump one chunk; from ldump.c */
int luaU_dump(
    lua_State* L, const Proto* f, lua_Writer w, void* data, int strip);

/* print one chunk; from print.c */
void luaU_print(const Proto* f, int full);

/* for header of binary files -- this is Lua 5.1 */
#define LUAC_VERSION 0x51

/* for header of binary files -- this is the official format */
#define LUAC_FORMAT 0

/* size of header of binary files */
#define LUAC_HEADERSIZE 12

#endif
