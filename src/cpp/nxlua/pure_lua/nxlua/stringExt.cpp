#include "stringExt.h"
#include "niu2x/pipe.h"

static const uint8_t luacode_bytearray[] = { 120, 156, 189, 85, 219, 114, 155,
    48, 16, 125, 174, 191, 98, 71, 41, 1, 106, 76, 237, 116, 166, 147, 166, 33,
    111, 253, 130, 190, 116, 198, 118, 50, 32, 139, 192, 68, 6, 42, 201, 185,
    76, 38, 253, 246, 174, 46, 198, 216, 6, 103, 250, 82, 63, 8, 179, 58, 123,
    246, 236, 106, 181, 228, 155, 138, 170, 178, 174, 64, 42, 81, 86, 247, 87,
    28, 31, 235, 32, 28, 125, 16, 76, 109, 4, 154, 25, 207, 175, 214, 169, 162,
    69, 224, 223, 206, 97, 161, 22, 213, 66, 44, 63, 5, 241, 36, 252, 232, 135,
    35, 86, 173, 70, 163, 252, 128, 67, 156, 226, 208, 158, 59, 158, 65, 142,
    62, 10, 167, 173, 229, 239, 117, 148, 13, 47, 85, 32, 89, 131, 206, 188,
    166, 41, 71, 223, 38, 130, 188, 100, 124, 37, 33, 209, 111, 80, 11, 32, 87,
    36, 130, 215, 183, 45, 166, 73, 149, 98, 24, 39, 113, 52, 113, 94, 11, 84,
    28, 144, 96, 126, 235, 201, 229, 56, 68, 180, 229, 52, 74, 238, 229, 38, 11,
    156, 15, 114, 59, 9, 1, 13, 93, 156, 249, 153, 125, 142, 103, 75, 164, 164,
    128, 74, 119, 185, 216, 173, 94, 245, 177, 84, 169, 80, 242, 169, 84, 69,
    240, 211, 88, 34, 248, 169, 77, 225, 8, 0, 182, 181, 112, 80, 148, 224, 48,
    179, 200, 217, 56, 171, 2, 139, 15, 147, 196, 252, 233, 15, 131, 198, 253,
    32, 63, 180, 192, 93, 8, 124, 133, 36, 241, 125, 93, 169, 227, 112, 147, 78,
    52, 237, 136, 177, 240, 97, 35, 217, 114, 222, 21, 106, 205, 101, 195, 104,
    153, 114, 90, 164, 66, 222, 73, 166, 176, 18, 88, 240, 222, 173, 57, 57, 39,
    186, 82, 228, 60, 93, 55, 223, 201, 0, 200, 39, 190, 5, 253, 222, 212, 106,
    16, 69, 124, 71, 117, 54, 253, 242, 109, 24, 117, 237, 80, 252, 4, 211, 141,
    195, 220, 107, 204, 81, 17, 15, 125, 130, 178, 106, 54, 246, 164, 0, 219, 7,
    30, 34, 120, 132, 178, 194, 222, 42, 113, 179, 55, 68, 8, 171, 218, 224,
    245, 207, 184, 239, 58, 208, 244, 152, 177, 69, 134, 202, 18, 235, 34, 195,
    238, 160, 204, 126, 255, 25, 11, 38, 85, 45, 216, 127, 84, 249, 136, 66,
    255, 85, 101, 197, 47, 50, 209, 213, 180, 223, 228, 93, 122, 178, 168, 240,
    22, 146, 235, 76, 192, 231, 27, 210, 127, 253, 99, 197, 158, 213, 133, 78,
    162, 203, 121, 66, 51, 89, 40, 77, 170, 81, 164, 23, 124, 170, 126, 167,
    120, 65, 211, 158, 87, 153, 196, 126, 238, 69, 15, 101, 222, 41, 150, 187,
    77, 109, 142, 27, 129, 87, 142, 214, 43, 166, 149, 4, 122, 217, 243, 36, 30,
    129, 56, 62, 156, 96, 222, 244, 226, 151, 158, 94, 214, 154, 189, 40, 102,
    61, 109, 1, 15, 235, 215, 134, 232, 42, 155, 76, 128, 214, 213, 35, 19, 10,
    120, 89, 49, 125, 188, 136, 149, 131, 53, 80, 181, 125, 115, 28, 237, 209,
    45, 4, 62, 91, 74, 38, 105, 218, 48, 72, 57, 7, 45, 40, 165, 56, 77, 37,
    100, 200, 150, 242, 166, 72, 171, 205, 154, 137, 146, 70, 224, 199, 62, 164,
    56, 144, 252, 137, 255, 110, 213, 245, 184, 126, 242, 98, 111, 2, 75, 61,
    178, 247, 10, 118, 148, 139, 108, 82, 202, 36, 168, 26, 200, 152, 128, 124,
    89, 103, 53, 151, 239, 53, 161, 57, 215, 241, 80, 251, 97, 64, 12, 118, 80,
    190, 30, 193, 208, 242, 141, 77, 251, 245, 183, 200, 62, 210, 243, 2, 239,
    217, 123, 214, 121, 181, 95, 156, 34, 60, 208, 234, 58, 131, 209, 7, 172,
    95, 198, 68, 80, 68, 179, 175, 97, 104, 191, 64, 239, 134, 48, 7, 100, 143,
    107, 168, 39, 143, 50, 86, 249, 165, 254, 16, 116, 242, 181, 93, 139, 70,
    216, 197, 25, 128, 228, 90, 10, 238, 117, 140, 180, 82, 218, 111, 218, 49,
    165, 66, 104, 211, 235, 52, 130, 233, 51, 53, 43, 51, 107, 110, 215, 75,
    179, 210, 55, 227, 242, 84, 148, 156, 89, 234, 63, 72, 211, 157, 93, 150,
    77, 173, 155, 157, 46, 115, 31, 92, 250, 19, 237, 20, 30, 160, 75, 208, 161,
    207, 80, 66, 187, 97, 35, 160, 101, 94, 46, 187, 244, 166, 188, 185, 225,
    191, 73, 182, 251, 170, 112, 217, 117, 127, 109, 226, 248, 152, 64, 121,
    180, 159, 9, 150, 62, 236, 89, 183, 19, 181, 141, 131, 238, 37, 250, 206,
    70, 125, 8, 93, 195, 196, 172, 99, 135, 56, 152, 200, 184, 165, 143, 243,
    47, 62, 2, 38, 218 };

#include <iostream>
#include <sstream>

void pure_lua_nxlua_stringExt_open(lua_State* L)
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