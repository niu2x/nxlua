#ifndef NXLUA_PURE_LUA_class
#define NXLUA_PURE_LUA_class
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
extern void pure_lua_class_open(lua_State* L);
#endif
