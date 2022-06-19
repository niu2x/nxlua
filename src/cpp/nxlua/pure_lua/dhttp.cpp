#include "dhttp.h"
#include "niu2x/pipe.h"

static const uint8_t luacode_bytearray[] = { 120, 156, 117, 81, 193, 78, 195,
    48, 12, 61, 55, 95, 225, 99, 145, 70, 53, 198, 173, 176, 221, 208, 126, 96,
    247, 106, 170, 93, 58, 148, 37, 93, 226, 50, 33, 196, 191, 99, 103, 105,
    215, 3, 92, 226, 248, 189, 103, 63, 199, 177, 190, 61, 90, 192, 158, 121,
    128, 45, 124, 255, 24, 211, 141, 174, 229, 147, 119, 55, 176, 126, 39, 46,
    199, 96, 87, 224, 7, 142, 15, 166, 208, 32, 202, 20, 124, 208, 138, 4, 85,
    129, 56, 124, 101, 34, 39, 66, 111, 140, 41, 236, 205, 98, 226, 80, 113,
    164, 142, 66, 32, 172, 28, 93, 203, 220, 181, 82, 9, 206, 5, 129, 46, 146,
    235, 12, 210, 238, 50, 82, 228, 134, 85, 42, 73, 29, 137, 27, 25, 74, 7, 91,
    32, 103, 226, 222, 99, 153, 74, 246, 111, 7, 97, 210, 53, 146, 195, 82, 52,
    43, 152, 158, 38, 89, 28, 132, 206, 78, 170, 106, 90, 143, 36, 126, 202,
    212, 51, 160, 126, 197, 169, 91, 40, 118, 91, 216, 172, 215, 112, 116, 184,
    0, 95, 225, 89, 48, 238, 201, 137, 188, 192, 90, 154, 120, 251, 73, 179, 13,
    217, 72, 202, 72, 167, 197, 122, 118, 112, 175, 249, 119, 135, 143, 240,
    148, 248, 191, 63, 227, 222, 58, 185, 126, 80, 203, 179, 105, 33, 207, 54,
    249, 148, 35, 237, 137, 199, 32, 255, 250, 98, 20, 52, 205, 190, 154, 254,
    61, 197, 95, 174, 69, 164, 217 };

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