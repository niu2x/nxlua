#include "class.h"
#include "niu2x/pipe.h"

static const uint8_t luacode_bytearray[] = { 120, 156, 109, 80, 65, 10, 195, 32,
    16, 60, 199, 87, 120, 180, 16, 124, 64, 161, 167, 30, 122, 236, 19, 130, 49,
    27, 72, 177, 107, 209, 149, 22, 74, 254, 94, 163, 209, 134, 180, 167, 145,
    25, 119, 102, 118, 141, 213, 202, 240, 94, 121, 56, 27, 229, 61, 63, 241,
    183, 94, 31, 228, 2, 204, 172, 74, 178, 235, 38, 28, 224, 21, 149, 202, 49,
    54, 6, 212, 52, 89, 252, 114, 71, 77, 214, 137, 3, 3, 28, 254, 202, 8, 79,
    33, 165, 60, 176, 198, 164, 236, 20, 119, 237, 111, 209, 215, 131, 25, 11,
    61, 161, 39, 133, 26, 150, 70, 51, 107, 60, 208, 29, 72, 145, 234, 13, 136,
    162, 181, 117, 56, 186, 21, 50, 231, 231, 4, 7, 20, 28, 86, 175, 220, 41,
    251, 215, 102, 201, 66, 248, 240, 0, 23, 39, 18, 46, 85, 18, 90, 183, 217,
    245, 183, 239, 238, 84, 77, 145, 54, 167, 42, 212, 110, 131, 66, 183, 188,
    4, 175, 85, 235, 255, 84, 181, 187, 200, 18, 145, 240, 3, 220, 16, 147,
    225 };

#include <iostream>
#include <sstream>

void pure_lua_class_open(lua_State* L)
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