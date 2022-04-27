changecom(@)dnl
changequote([,])dnl
#include "[]NAME[].h[]"
static const char *source = R"RAW(
LUA
)RAW";

#include <iostream>
void pure_lua_[]NAME[]_open(lua_State *L) {
	if(luaL_dostring(L, source)){
        std::cerr << lua_tostring(L, -1) << std::endl;
    }
}

