#!/usr/bin/env nxlua
local luas = {}
for i = 2, #sys.argv do
	table.insert(luas, string.sub(sys.argv[i], 1, -5))
end


local output = lupa.expand([====[
{% for i, v in ipairs(luas) %}#include "pure_lua/{{v}}.h"
{% endfor %}
void pure_lua_open(lua_State* L)
{
	{% for i, v in ipairs(luas) %}pure_lua_{{v}}_open(L);
{% endfor %}
}
]====], {
    luas = luas,
})

io.stdout:write(output)