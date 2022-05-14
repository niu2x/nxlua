#include "class.h"
#include "niu2x/pipe.h"

static const uint8_t luacode_bytearray[] = { 120, 156, 109, 144, 65, 14, 194,
    32, 16, 69, 215, 229, 20, 44, 49, 105, 56, 128, 137, 43, 23, 46, 61, 2, 161,
    116, 154, 212, 224, 96, 128, 70, 19, 211, 187, 75, 161, 131, 77, 117, 53,
    228, 127, 248, 255, 13, 214, 25, 109, 121, 167, 3, 156, 173, 14, 129, 159,
    248, 219, 172, 135, 232, 39, 152, 89, 181, 164, 82, 35, 246, 240, 74, 78,
    213, 24, 27, 38, 52, 113, 116, 248, 213, 142, 38, 58, 47, 14, 12, 176, 255,
    107, 35, 60, 149, 93, 90, 133, 148, 242, 192, 154, 124, 230, 185, 244, 218,
    221, 82, 122, 0, 59, 144, 60, 98, 136, 26, 13, 44, 92, 51, 107, 2, 196, 59,
    68, 29, 117, 103, 65, 144, 215, 214, 199, 41, 141, 196, 66, 81, 26, 60, 196,
    201, 99, 205, 42, 100, 37, 191, 242, 229, 8, 17, 166, 7, 248, 244, 34, 207,
    5, 37, 79, 231, 55, 27, 255, 242, 238, 62, 172, 33, 107, 243, 97, 36, 237,
    54, 32, 185, 229, 84, 188, 162, 214, 251, 25, 85, 93, 36, 85, 228, 249, 1,
    209, 175, 150, 75 };

#include <iostream>
#include <sstream>

void pure_lua_nxlua_class_open(lua_State* L)
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
