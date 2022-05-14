#ifndef NXLUA_PURE_LUA_re
#define NXLUA_PURE_LUA_re
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
extern void pure_lua_re_open(lua_State* L);
#endif
