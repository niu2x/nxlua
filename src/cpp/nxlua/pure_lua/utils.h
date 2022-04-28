#ifndef NXLUA_PURE_LUA_utils
#define NXLUA_PURE_LUA_utils
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
extern void pure_lua_utils_open(lua_State* L);
#endif
