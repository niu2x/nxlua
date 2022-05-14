#include "mathExt.h"
#include "niu2x/pipe.h"

static const uint8_t luacode_bytearray[] = { 120, 156, 117, 141, 77, 18, 130,
    48, 12, 133, 215, 228, 20, 89, 86, 198, 202, 207, 202, 133, 122, 151, 14,
    164, 208, 25, 26, 25, 104, 29, 142, 111, 68, 20, 29, 101, 209, 38, 121, 239,
    125, 137, 141, 92, 5, 119, 101, 244, 38, 180, 135, 170, 51, 190, 87, 55,
    211, 69, 218, 163, 119, 44, 159, 153, 118, 144, 204, 10, 158, 159, 33, 209,
    223, 145, 63, 174, 153, 62, 22, 136, 59, 80, 136, 3, 227, 172, 1, 113, 13,
    160, 181, 6, 251, 117, 119, 48, 117, 89, 83, 163, 164, 174, 132, 12, 217,
    236, 246, 46, 45, 142, 249, 22, 43, 92, 41, 81, 37, 117, 101, 101, 200, 132,
    73, 23, 126, 139, 29, 93, 195, 138, 163, 23, 208, 89, 148, 6, 47, 152, 99,
    104, 137, 33, 121, 173, 42, 32, 161, 110, 164, 197, 63, 253, 248, 122, 9,
    172, 74, 46, 130, 220, 123, 188, 59, 5, 73, 111, 19 };

#include <iostream>
#include <sstream>

void pure_lua_nxlua_mathExt_open(lua_State* L)
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
