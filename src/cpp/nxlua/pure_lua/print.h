#ifndef NXLUA_PURE_LUA_print
#define NXLUA_PURE_LUA_print
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
extern void pure_lua_print_open(lua_State* L);
#endif
