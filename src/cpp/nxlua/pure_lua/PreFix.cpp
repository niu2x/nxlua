#include "PreFix.h"
#include "niu2x/pipe.h"

static const uint8_t luacode_bytearray[] = { 120, 156, 75, 203, 47, 82, 200,
    214, 81, 40, 83, 200, 204, 83, 40, 72, 204, 44, 42, 214, 200, 47, 142, 79,
    173, 40, 209, 84, 72, 201, 231, 226, 204, 47, 142, 206, 142, 85, 176, 85,
    40, 227, 74, 205, 75, 1, 0, 57, 65, 13, 237 };

#include <iostream>
#include <sstream>

void pure_lua_PreFix_open(lua_State* L)
{

    std::string luacode(
        luacode_bytearray, luacode_bytearray + sizeof(luacode_bytearray));
    std::istringstream is(luacode);
    nx::pipe::source_t source(is);

    std::stringstream out;
    nx::pipe::sink_t sink(out);

    nx::pipe::filter::unzlib_t unzlib;

    source | unzlib | sink;

    if (luaL_dostring(L, out.str().c_str())) {
        std::cerr << lua_tostring(L, -1) << std::endl;
    }
}