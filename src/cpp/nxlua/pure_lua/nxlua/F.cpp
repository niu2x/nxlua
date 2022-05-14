#include "F.h"
#include "niu2x/pipe.h"

static const uint8_t luacode_bytearray[] = { 120, 156, 157, 85, 91, 107, 219,
    48, 20, 126, 247, 175, 56, 8, 66, 228, 77, 53, 107, 198, 246, 16, 200, 99,
    51, 10, 163, 131, 13, 250, 234, 202, 177, 156, 152, 56, 82, 144, 229, 182,
    16, 242, 223, 119, 116, 177, 45, 55, 105, 7, 51, 196, 118, 142, 190, 243,
    157, 251, 113, 163, 54, 188, 129, 53, 172, 224, 116, 78, 146, 198, 253, 107,
    20, 47, 81, 96, 31, 73, 82, 87, 144, 63, 222, 253, 254, 115, 255, 235, 1,
    86, 43, 32, 63, 59, 14, 223, 178, 91, 2, 102, 39, 100, 2, 208, 163, 171, 78,
    110, 76, 173, 36, 221, 168, 82, 48, 144, 252, 128, 247, 156, 129, 144, 207,
    169, 133, 57, 164, 101, 175, 36, 10, 181, 14, 6, 90, 163, 107, 185, 141,
    148, 122, 48, 218, 173, 228, 96, 196, 95, 173, 48, 21, 242, 81, 71, 49, 242,
    226, 165, 133, 233, 180, 68, 141, 32, 18, 178, 76, 38, 39, 178, 110, 156,
    217, 36, 28, 218, 95, 8, 183, 247, 28, 218, 13, 151, 121, 215, 90, 127, 236,
    171, 20, 154, 1, 215, 91, 134, 118, 185, 222, 236, 68, 153, 38, 67, 20, 53,
    250, 127, 155, 56, 254, 163, 224, 102, 18, 161, 143, 253, 153, 55, 157, 64,
    84, 160, 162, 142, 169, 142, 194, 179, 48, 155, 210, 158, 253, 77, 176, 193,
    113, 163, 187, 158, 236, 34, 54, 235, 68, 13, 159, 189, 35, 157, 52, 117,
    51, 144, 98, 188, 73, 148, 23, 222, 180, 226, 122, 204, 178, 164, 88, 165,
    34, 237, 161, 5, 92, 131, 85, 74, 31, 184, 177, 72, 44, 88, 148, 6, 213, 25,
    161, 115, 172, 5, 122, 146, 223, 61, 60, 2, 151, 37, 80, 75, 26, 37, 179,
    20, 69, 183, 205, 182, 194, 56, 29, 6, 95, 25, 16, 11, 38, 105, 10, 74, 195,
    123, 232, 238, 232, 162, 102, 48, 72, 106, 89, 41, 186, 64, 237, 138, 164,
    153, 245, 109, 74, 100, 95, 221, 203, 54, 244, 201, 34, 141, 114, 64, 209,
    243, 229, 182, 237, 10, 74, 102, 197, 233, 76, 216, 216, 178, 5, 58, 182,
    143, 42, 227, 155, 50, 179, 88, 119, 196, 22, 108, 145, 218, 172, 206, 79,
    115, 23, 225, 5, 0, 110, 22, 236, 38, 96, 206, 243, 235, 149, 188, 84, 90,
    88, 189, 52, 42, 235, 164, 141, 252, 76, 84, 7, 131, 185, 117, 10, 75, 44,
    193, 102, 71, 201, 137, 102, 159, 210, 37, 157, 205, 240, 113, 38, 189, 190,
    133, 35, 210, 61, 48, 7, 151, 26, 35, 212, 243, 139, 215, 99, 168, 28, 142,
    254, 48, 96, 7, 97, 184, 225, 69, 35, 104, 56, 103, 112, 130, 60, 175, 101,
    41, 94, 227, 49, 199, 86, 216, 71, 3, 24, 54, 135, 120, 22, 13, 162, 190,
    143, 7, 47, 187, 186, 17, 174, 139, 161, 84, 163, 120, 92, 7, 72, 120, 143,
    117, 69, 173, 105, 157, 29, 151, 175, 245, 68, 205, 78, 142, 50, 163, 158,
    205, 53, 20, 90, 240, 125, 52, 25, 177, 5, 181, 159, 14, 227, 187, 125, 214,
    83, 134, 214, 218, 95, 216, 85, 123, 111, 45, 20, 212, 147, 190, 53, 250,
    47, 115, 97, 8, 124, 170, 112, 118, 255, 219, 80, 159, 236, 129, 105, 60,
    157, 64, 3, 137, 230, 47, 104, 157, 14, 19, 27, 217, 69, 56, 156, 63, 218,
    210, 148, 4, 18, 146, 101, 190, 45, 9, 118, 135, 22, 109, 107, 151, 195, 83,
    144, 102, 25, 121, 194, 177, 34, 6, 111, 161, 121, 62, 218, 230, 253, 110,
    194, 6, 143, 102, 42, 108, 26, 148, 98, 65, 36, 245, 147, 109, 84, 248, 78,
    56, 73, 239, 181, 221, 105, 99, 200, 90, 43, 77, 241, 206, 224, 75, 28, 87,
    127, 133, 197, 143, 218, 110, 208, 38, 157, 190, 198, 30, 183, 231, 121,
    142, 161, 219, 148, 122, 39, 18, 204, 73, 146, 255, 200, 236, 215, 113, 253,
    23, 63, 146, 22, 215 };

#include <iostream>
#include <sstream>

void pure_lua_nxlua_F_open(lua_State* L)
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
