#include "welcome.h"
static const char* source = R"RAW(

)RAW";

#include <iostream>
void pure_lua_welcome_open(lua_State* L)
{
    if (luaL_dostring(L, source)) {
        {
            std::cerr << lua_tostring(L, -1) << std::endl;
        }
    }
}
