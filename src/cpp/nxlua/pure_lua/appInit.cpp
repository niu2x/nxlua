#include "appInit.h"
static const char* source = R"RAW(
-- print([==[todo add script root dir to package.path]==])
)RAW";

#include <iostream>
void pure_lua_appInit_open(lua_State* L)
{
    if (luaL_dostring(L, source)) {
        std::cerr << lua_tostring(L, -1) << std::endl;
    }
}
