#!/usr/bin/env nxlua
local modulename = sys.argv[2]

local function usage( ... )
    print(string.format("Usage: %s modulename", sys.argv[1]))
    os.exit(1)
end

if modulename == nil then
    print(sys.argv[1], "invalid arguments")
    usage()
end

local output = lupa.expand([====[
#ifndef NXLUA_PURE_LUA_{{modulename}}
#define NXLUA_PURE_LUA_{{modulename}}
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
extern void pure_lua_{{modulename}}_open(lua_State *L);
#endif

]====], {
    modulename = modulename,
})

io.stdout:write(output)