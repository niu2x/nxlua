#include "welcome.h"
#include "niu2x/pipe.h"

static const uint8_t luacode_bytearray[] = { 120, 156, 3, 0, 0, 0, 0, 1 };

#include <iostream>
#include <sstream>

void pure_lua_welcome_open(lua_State* L)
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
