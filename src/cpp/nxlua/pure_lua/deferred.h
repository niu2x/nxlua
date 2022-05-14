#ifndef NXLUA_PURE_LUA_deferred
#define NXLUA_PURE_LUA_deferred
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
extern void pure_lua_deferred_open(lua_State* L);
#endif
