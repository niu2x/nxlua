#ifndef NXLUA_PURE_LUA_lupa
#define NXLUA_PURE_LUA_lupa
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
extern void pure_lua_lupa_open(lua_State* L);
#endif
