#ifndef NXLUA_PURE_LUA_PreFix
#define NXLUA_PURE_LUA_PreFix
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
extern void pure_lua_PreFix_open(lua_State* L);
#endif
