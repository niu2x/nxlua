#include "appInit.h"
static const char* source = R"RAW(
-- print([==[todo add script root dir to package.path]==])
local non_interactive = sys.argv[1] ~= nil
if non_interactive then
	local launcher = sys.argv[1]
	if os.is_relative(launcher) then
		launcher = path_utils:join(os.getcwd(), sys.argv[1])
	end
	sys.launcher = launcher
	package.path = string.format("%s/?.lua;", path_utils:dirname(launcher)) .. package.path 
end
)RAW";

#include <iostream>
void pure_lua_appInit_open(lua_State* L)
{
    if (luaL_dostring(L, source)) {
        std::cerr << lua_tostring(L, -1) << std::endl;
    }
}
