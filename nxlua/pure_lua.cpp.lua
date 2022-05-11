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
luacode = pipe.pipe(luacode, "zlib(6)")

local luacode_bytearray = {}

for i = 1, #luacode do
	local v = string.byte(string.sub(luacode, i, i))
	table.insert(luacode_bytearray, v)
end

local op = '{'
local cp = '}'

luacode_bytearray = table.concat(luacode_bytearray, ',')

local output = F[====[
#include "{modulename}.h"
#include "niu2x/pipe.h"

static const uint8_t luacode_bytearray[] = {op}
	{luacode_bytearray}
{cp};

#include <iostream>
#include <sstream>

void pure_lua_{modulename}_open(lua_State* L)
{op}
	
	std::string luacode(luacode_bytearray, luacode_bytearray+sizeof(luacode_bytearray));
	std::istringstream is(luacode);
    nx::pipe::source_t source(is);

    std::stringstream out;
    nx::pipe::sink_t sink(out);

    nx::pipe::filter::unzlib_t unzlib;

    source| unzlib| sink;

    if (luaL_dostring(L, out.str().c_str())) {op}
        std::cerr << lua_tostring(L, -1) << std::endl;
    {cp}
{cp}
]====]

io.stdout:write(output)