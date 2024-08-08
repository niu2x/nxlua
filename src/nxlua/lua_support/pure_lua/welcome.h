#ifndef NXLUA_PURE_LUA_welcome
#define NXLUA_PURE_LUA_welcome
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
extern void pure_lua_welcome_open(lua_State* L);
#endif
