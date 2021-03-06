#include "appInit.h"
#include "niu2x/pipe.h"

static const uint8_t luacode_bytearray[] = { 120, 156, 101, 144, 193, 106, 3,
    49, 12, 68, 207, 246, 87, 136, 64, 193, 11, 137, 75, 175, 45, 38, 31, 178,
    44, 139, 176, 157, 93, 183, 142, 181, 216, 218, 148, 94, 250, 237, 181, 105,
    3, 14, 189, 9, 161, 55, 51, 154, 211, 9, 182, 28, 18, 171, 209, 152, 145,
    201, 17, 160, 115, 80, 108, 14, 27, 67, 38, 98, 112, 33, 3, 19, 108, 104,
    63, 112, 241, 122, 67, 94, 39, 99, 166, 65, 70, 178, 24, 33, 81, 154, 43,
    239, 51, 90, 14, 55, 15, 6, 202, 87, 209, 152, 151, 219, 248, 50, 193, 183,
    129, 20, 162, 12, 151, 127, 119, 188, 250, 36, 197, 175, 70, 196, 61, 217,
    213, 231, 71, 88, 138, 138, 81, 209, 161, 204, 217, 71, 108, 148, 186, 95,
    14, 127, 188, 232, 208, 150, 108, 222, 57, 196, 242, 250, 78, 33, 169, 138,
    46, 158, 237, 167, 83, 195, 177, 215, 29, 164, 240, 201, 73, 209, 86, 29,
    126, 31, 165, 232, 95, 109, 145, 184, 22, 180, 232, 11, 229, 43, 178, 58,
    60, 149, 231, 179, 142, 59, 190, 29, 142, 189, 101, 173, 41, 225, 181, 75,
    56, 128, 214, 15, 173, 129, 108, 182, 242, 7, 143, 142, 127, 98 };

#include <iostream>
#include <sstream>

void pure_lua_appInit_open(lua_State* L)
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