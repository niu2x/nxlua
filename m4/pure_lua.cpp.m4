changecom(@)dnl
changequote([,])dnl
#include "[]NAME[].h[]"
static const char *source = R"RAW(
LUA
)RAW";


void pure_lua_[]NAME[]_open(lua_State *L) {
	luaL_dostring(L, source);
}

