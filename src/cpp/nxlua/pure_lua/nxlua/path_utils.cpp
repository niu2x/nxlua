#include "path_utils.h"
#include "niu2x/pipe.h"

static const uint8_t luacode_bytearray[] = { 120, 156, 173, 84, 65, 110, 131,
    48, 16, 60, 227, 87, 172, 148, 3, 88, 34, 84, 228, 152, 138, 94, 251, 136,
    166, 138, 72, 48, 193, 149, 99, 34, 108, 148, 170, 85, 255, 94, 123, 141,
    147, 0, 110, 164, 74, 57, 89, 182, 103, 199, 179, 179, 3, 162, 221, 151, 2,
    78, 165, 110, 182, 189, 230, 66, 65, 1, 223, 63, 132, 212, 189, 220, 107,
    222, 202, 155, 155, 245, 71, 203, 101, 130, 7, 121, 138, 203, 10, 40, 137,
    120, 13, 74, 119, 92, 30, 50, 213, 239, 18, 60, 78, 193, 0, 114, 10, 69, 1,
    241, 83, 12, 186, 97, 146, 68, 145, 171, 40, 2, 232, 149, 161, 97, 178, 10,
    113, 25, 162, 197, 104, 13, 177, 230, 115, 214, 28, 53, 44, 47, 204, 29,
    211, 125, 39, 65, 49, 81, 175, 101, 219, 29, 75, 193, 191, 152, 67, 66, 150,
    33, 161, 89, 80, 15, 37, 182, 34, 232, 64, 197, 59, 89, 30, 153, 51, 193,
    54, 143, 107, 17, 162, 53, 151, 2, 173, 221, 149, 138, 217, 34, 15, 243,
    123, 143, 10, 43, 155, 180, 99, 187, 89, 38, 11, 95, 75, 151, 57, 189, 35,
    243, 242, 196, 127, 116, 214, 156, 137, 202, 142, 223, 158, 174, 213, 73,
    112, 157, 24, 91, 40, 180, 157, 77, 132, 157, 205, 98, 192, 188, 20, 144,
    123, 255, 7, 249, 238, 230, 109, 64, 188, 143, 93, 183, 140, 207, 127, 203,
    189, 10, 154, 234, 69, 41, 7, 107, 66, 188, 217, 196, 169, 29, 19, 37, 36,
    58, 55, 92, 48, 63, 113, 67, 171, 206, 92, 55, 131, 79, 40, 185, 106, 135,
    100, 204, 131, 129, 185, 192, 40, 25, 15, 157, 76, 236, 205, 161, 77, 180,
    70, 201, 2, 204, 218, 188, 27, 215, 76, 184, 29, 180, 142, 125, 234, 135,
    166, 100, 50, 35, 127, 237, 231, 148, 93, 230, 228, 161, 70, 128, 21, 31,
    79, 7, 183, 242, 237, 57, 64, 120, 110, 119, 172, 51, 41, 52, 149, 20, 191,
    172, 27, 67, 82, 251, 160, 119, 133, 108, 95, 179, 209, 31, 229, 186, 249,
    5, 142, 164, 106, 28 };

#include <iostream>
#include <sstream>

void pure_lua_nxlua_path_utils_open(lua_State* L)
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