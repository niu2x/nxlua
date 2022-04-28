#include "PreFix.h"
static const char* source = R"RAW(
for k, v in pairs(os_ext) do
	os[k] = v
end
)RAW";

#include <iostream>
void pure_lua_PreFix_open(lua_State* L)
{
    if (luaL_dostring(L, source)) {
        std::cerr << lua_tostring(L, -1) << std::endl;
    }
}
