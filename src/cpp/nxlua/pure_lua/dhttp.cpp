#include "dhttp.h"
#include "niu2x/pipe.h"

static const uint8_t luacode_bytearray[] = { 120, 156, 77, 144, 187, 14, 194,
    48, 12, 69, 231, 230, 43, 50, 6, 9, 85, 21, 108, 225, 177, 161, 254, 0, 123,
    85, 213, 46, 45, 10, 73, 73, 92, 24, 16, 255, 142, 211, 23, 93, 18, 251,
    158, 107, 59, 177, 113, 85, 105, 36, 52, 68, 157, 60, 201, 207, 87, 136,
    186, 183, 21, 181, 206, 142, 162, 190, 33, 169, 222, 155, 141, 72, 204, 104,
    101, 27, 96, 141, 222, 35, 164, 22, 223, 106, 33, 30, 159, 204, 98, 81, 202,
    97, 143, 129, 10, 138, 148, 19, 29, 144, 10, 238, 50, 117, 154, 149, 7, 82,
    227, 64, 13, 37, 249, 229, 202, 100, 8, 3, 90, 80, 236, 217, 202, 249, 45,
    156, 133, 142, 241, 52, 41, 186, 138, 202, 1, 242, 188, 72, 244, 34, 196,
    121, 73, 91, 175, 28, 231, 147, 220, 101, 153, 44, 45, 172, 196, 163, 220,
    179, 70, 13, 90, 182, 39, 160, 185, 137, 51, 47, 92, 198, 160, 9, 56, 147,
    59, 86, 244, 7, 22, 68, 60, 134, 79, 80, 239, 121, 75, 7, 17, 69, 81, 228,
    233, 188, 197, 225, 254, 1, 167, 101, 111, 117 };

#include <iostream>
#include <sstream>

void pure_lua_dhttp_open(lua_State* L)
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