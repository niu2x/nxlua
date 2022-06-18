#include "http.h"
#include "niu2x/pipe.h"

static const uint8_t luacode_bytearray[] = { 120, 156, 77, 141, 65, 14, 194, 32,
    16, 69, 215, 237, 41, 102, 73, 19, 99, 26, 221, 17, 235, 206, 120, 1, 247,
    164, 129, 65, 154, 32, 180, 101, 184, 191, 3, 65, 211, 205, 192, 252, 247,
    224, 219, 28, 52, 45, 49, 128, 35, 90, 229, 27, 73, 228, 221, 15, 125, 231,
    163, 158, 61, 236, 184, 193, 84, 209, 153, 175, 25, 19, 41, 18, 76, 121,
    145, 9, 73, 177, 219, 252, 95, 242, 65, 114, 209, 136, 250, 228, 249, 120,
    49, 169, 31, 39, 12, 70, 176, 115, 2, 219, 10, 121, 75, 43, 227, 214, 84,
    44, 165, 163, 65, 238, 43, 68, 254, 131, 210, 215, 45, 246, 96, 220, 39,
    184, 140, 35, 204, 193, 28, 194, 27, 92, 57, 35, 135, 129, 117, 244, 9, 203,
    17, 76, 95, 198, 208, 243, 248, 2, 222, 153, 76, 228 };

#include <iostream>
#include <sstream>

void pure_lua_http_open(lua_State* L)
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