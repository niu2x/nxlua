#ifndef NXLUA_PURE_LUA_F
#define NXLUA_PURE_LUA_F
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
extern void pure_lua_F_open(lua_State* L);
#endif
