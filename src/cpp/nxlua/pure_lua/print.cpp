#include "print.h"
#include "niu2x/pipe.h"

static const uint8_t luacode_bytearray[] = { 120, 156, 125, 143, 77, 14, 194,
    32, 16, 133, 215, 112, 138, 217, 181, 36, 134, 3, 152, 116, 237, 37, 76, 12,
    182, 160, 19, 9, 52, 48, 173, 49, 70, 207, 238, 244, 55, 70, 141, 27, 24,
    248, 222, 123, 240, 124, 172, 141, 135, 232, 155, 54, 97, 32, 168, 224, 176,
    211, 227, 40, 151, 129, 239, 92, 23, 106, 194, 24, 160, 4, 173, 53, 40, 41,
    252, 104, 115, 152, 242, 192, 41, 117, 86, 10, 23, 19, 92, 54, 208, 3, 6,
    192, 214, 48, 43, 239, 44, 127, 40, 104, 162, 20, 2, 221, 172, 167, 179, 13,
    124, 22, 139, 219, 25, 159, 217, 46, 236, 180, 9, 140, 58, 83, 19, 59, 218,
    94, 19, 146, 45, 11, 40, 212, 128, 67, 51, 165, 208, 173, 181, 101, 175,
    160, 170, 160, 32, 115, 244, 182, 88, 35, 63, 173, 35, 214, 20, 51, 113,
    147, 19, 155, 212, 252, 206, 91, 204, 147, 99, 38, 254, 39, 231, 59, 225,
    151, 172, 95, 255, 57, 46, 95, 69, 246, 129, 155, 12, 232, 5, 19, 213, 116,
    31 };

#include <iostream>
#include <sstream>

void pure_lua_print_open(lua_State* L)
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
