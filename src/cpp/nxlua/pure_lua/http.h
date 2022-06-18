#ifndef NXLUA_PURE_LUA_http
#define NXLUA_PURE_LUA_http
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
extern void pure_lua_http_open(lua_State* L);
#endif
