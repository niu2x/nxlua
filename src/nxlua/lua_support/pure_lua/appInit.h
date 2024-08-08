#ifndef NXLUA_PURE_LUA_appInit
#define NXLUA_PURE_LUA_appInit
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
extern void pure_lua_appInit_open(lua_State* L);
#endif
