#include "Image.h"
#include "niu2x/pipe.h"

static const uint8_t luacode_bytearray[] = { 120, 156, 189, 86, 77, 143, 219,
    32, 16, 61, 39, 191, 130, 35, 105, 201, 199, 102, 115, 138, 212, 115, 213,
    123, 239, 22, 235, 144, 216, 90, 108, 34, 32, 141, 221, 95, 223, 225, 211,
    96, 123, 211, 70, 85, 43, 173, 86, 206, 188, 247, 102, 30, 51, 128, 93, 124,
    221, 124, 107, 232, 133, 161, 47, 168, 228, 84, 41, 188, 90, 46, 207, 183,
    182, 212, 181, 104, 145, 69, 142, 165, 22, 18, 194, 11, 197, 248, 121, 243,
    70, 203, 119, 214, 158, 10, 224, 215, 6, 45, 52, 64, 16, 152, 168, 184, 160,
    39, 124, 165, 186, 106, 105, 195, 64, 45, 153, 190, 201, 22, 101, 73, 198,
    164, 185, 60, 138, 254, 96, 191, 205, 51, 34, 205, 229, 185, 215, 39, 93,
    97, 180, 217, 108, 208, 71, 89, 28, 101, 94, 94, 177, 250, 82, 233, 199,
    122, 207, 153, 79, 32, 153, 170, 127, 50, 124, 39, 168, 26, 247, 50, 199,
    230, 196, 231, 154, 115, 44, 201, 133, 188, 17, 58, 81, 231, 160, 149, 115,
    81, 82, 142, 98, 18, 41, 52, 213, 172, 184, 138, 186, 213, 184, 35, 168, 39,
    136, 182, 23, 158, 180, 179, 67, 159, 80, 3, 253, 219, 148, 66, 97, 135,
    161, 53, 234, 67, 84, 213, 173, 143, 18, 52, 112, 135, 40, 250, 60, 112,
    135, 12, 206, 203, 164, 17, 214, 76, 160, 44, 156, 213, 138, 242, 115, 113,
    135, 77, 101, 150, 22, 6, 177, 221, 103, 112, 21, 224, 208, 231, 1, 239, 94,
    96, 81, 47, 128, 175, 93, 34, 226, 31, 170, 72, 216, 3, 97, 159, 18, 70,
    248, 43, 224, 175, 128, 127, 0, 31, 0, 62, 36, 112, 72, 191, 92, 196, 210,
    121, 147, 109, 116, 104, 115, 172, 159, 179, 108, 52, 97, 5, 23, 57, 203,
    70, 19, 86, 48, 147, 179, 108, 52, 178, 130, 243, 134, 118, 69, 7, 92, 59,
    26, 248, 129, 227, 131, 177, 216, 237, 97, 160, 67, 4, 138, 116, 135, 213,
    42, 213, 246, 179, 90, 179, 180, 62, 211, 26, 131, 189, 209, 70, 113, 221,
    38, 133, 97, 167, 196, 135, 81, 97, 19, 25, 23, 6, 109, 63, 171, 29, 21, 54,
    145, 88, 56, 168, 91, 118, 183, 91, 201, 45, 125, 237, 156, 164, 96, 229,
    193, 222, 131, 125, 148, 194, 65, 188, 113, 13, 176, 219, 170, 134, 108, 1,
    108, 79, 138, 193, 194, 89, 181, 69, 136, 75, 55, 128, 246, 40, 238, 8, 242,
    127, 137, 41, 45, 105, 171, 206, 66, 54, 195, 197, 25, 34, 133, 62, 218,
    103, 110, 142, 197, 218, 38, 222, 194, 166, 176, 79, 213, 118, 15, 217, 83,
    113, 124, 62, 54, 55, 142, 167, 169, 178, 227, 245, 164, 118, 176, 145, 31,
    3, 147, 199, 179, 205, 250, 105, 115, 229, 12, 47, 23, 249, 61, 20, 86, 157,
    158, 96, 146, 31, 88, 2, 26, 215, 169, 137, 42, 237, 167, 161, 69, 91, 203,
    133, 217, 83, 254, 154, 114, 226, 229, 236, 29, 89, 74, 113, 245, 151, 155,
    191, 100, 159, 157, 169, 147, 61, 59, 177, 29, 34, 187, 63, 235, 207, 96,
    238, 65, 35, 2, 252, 176, 1, 179, 47, 74, 48, 205, 190, 11, 252, 31, 22,
    111, 75, 225, 236, 170, 190, 35, 146, 223, 205, 213, 191, 223, 51, 127, 215,
    42, 172, 96, 30, 170, 55, 175, 83, 115, 215, 192, 63, 33, 145, 234, 178,
    119, 123, 108, 170, 55, 30, 60, 194, 187, 14, 212, 33, 24, 172, 154, 104,
    111, 60, 216, 154, 235, 181, 29, 56, 170, 21, 226, 236, 172, 181, 184, 162,
    171, 80, 181, 177, 49, 246, 115, 146, 244, 142, 149, 44, 221, 22, 1, 71,
    160, 117, 115, 128, 96, 97, 107, 26, 135, 178, 140, 159, 40, 57, 195, 25,
    240, 148, 248, 21, 146, 144, 30, 142, 211, 167, 155, 25, 22, 68, 23, 144,
    114, 58, 174, 224, 138, 36, 229, 137, 231, 207, 237, 249, 71, 130, 100, 122,
    240, 115, 242, 117, 19, 122, 51, 202, 185, 178, 151, 192, 47, 88, 49, 121,
    14 };

#include <iostream>
#include <sstream>

void pure_lua_nxlua_Image_open(lua_State* L)
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