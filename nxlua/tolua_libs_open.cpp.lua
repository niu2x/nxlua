#!/usr/bin/env nxlua
local luas = {}
for i = 2, #sys.argv do
	table.insert(luas, path_utils:basename(string.sub(sys.argv[i], 1, -5)))
end


local output = lupa.expand([====[
#include <tolua++.h>
{% for i, v in ipairs(luas) %}TOLUA_API int tolua_{{v}}_open(lua_State* tolua_S);
{% endfor %}
void tolua_libs_open(lua_State* L)
{
	{% for i, v in ipairs(luas) %}tolua_{{v}}_open(L);
{% endfor %}
}
]====], {
    luas = luas,
})

io.stdout:write(output)
