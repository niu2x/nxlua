#!/usr/bin/env nxlua

local luafile = sys.argv[2]
local modulename = sys.argv[3]

local function usage( ... )
	print(string.format("Usage: %s luafile modulename", sys.argv[1]))
	os.exit(1)
end

if luafile == nil or modulename == nil then
	print(sys.argv[1], "invalid arguments")
	usage()
end

local function readfile( pathname )
	local f = io.open(pathname)
	local v = f:read('*all')
	f:close()
	return v
end

local function writefile( pathname, content )
	local f = io.open(pathname, 'wb')
	f:write(content)
	f:close()
end

local luacode = readfile(luafile)

local output = F[====[
#include "{modulename}.h"
static const char* source = R"RAW(
{luacode}
)RAW";

#include <iostream>
void pure_lua_{modulename}_open(lua_State* L)
{{
    if (luaL_dostring(L, source)) {{
        std::cerr << lua_tostring(L, -1) << std::endl;
    }}
}}
]====]

io.stdout:write(output)