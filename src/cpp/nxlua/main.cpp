extern "C" {
#include "lua.h"
#include "lauxlib.h"
}

int main()
{
    auto L = luaL_newstate();
    lua_close(L);
    return 0;
}