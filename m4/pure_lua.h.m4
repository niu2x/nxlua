changecom(@)dnl
changequote([,])dnl
#ifndef NXLUA_PURE_LUA_[]NAME
#define NXLUA_PURE_LUA_[]NAME
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
extern void pure_lua_[]NAME[]_open(lua_State *L);
#endif
