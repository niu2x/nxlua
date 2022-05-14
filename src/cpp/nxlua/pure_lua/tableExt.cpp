#include "tableExt.h"
#include "niu2x/pipe.h"

static const uint8_t luacode_bytearray[] = { 120, 156, 189, 88, 79, 111, 171,
    70, 16, 63, 195, 167, 88, 17, 85, 2, 61, 98, 217, 189, 188, 67, 158, 35,
    181, 213, 59, 68, 149, 218, 91, 47, 174, 21, 97, 188, 36, 91, 99, 32, 176,
    240, 94, 26, 165, 159, 189, 51, 59, 187, 203, 98, 192, 118, 164, 170, 62, 4,
    152, 157, 217, 249, 205, 223, 157, 77, 214, 22, 169, 20, 101, 193, 100, 178,
    203, 249, 130, 39, 233, 115, 40, 99, 150, 1, 57, 242, 189, 172, 172, 217,
    33, 102, 29, 19, 5, 171, 18, 81, 55, 161, 140, 216, 190, 244, 61, 79, 100,
    138, 39, 236, 98, 118, 136, 216, 122, 205, 100, 221, 114, 38, 159, 121, 1,
    139, 94, 205, 101, 91, 23, 138, 6, 159, 188, 216, 251, 244, 71, 211, 179,
    36, 111, 184, 143, 20, 63, 27, 234, 23, 197, 158, 127, 255, 58, 6, 161, 232,
    108, 205, 86, 49, 187, 145, 67, 4, 114, 163, 22, 183, 49, 49, 253, 135, 96,
    106, 222, 241, 186, 225, 15, 23, 48, 221, 0, 25, 112, 221, 174, 254, 47, 92,
    153, 200, 37, 175, 29, 52, 121, 153, 38, 57, 3, 57, 64, 243, 246, 126, 85,
    216, 198, 112, 76, 0, 26, 94, 203, 16, 246, 2, 249, 104, 10, 23, 60, 38, 81,
    29, 147, 42, 68, 82, 204, 22, 139, 133, 5, 85, 37, 117, 210, 32, 44, 32,
    190, 27, 162, 18, 64, 170, 90, 189, 10, 191, 146, 216, 172, 182, 218, 14,
    146, 232, 146, 188, 85, 251, 160, 144, 146, 122, 140, 153, 68, 41, 225, 138,
    105, 25, 143, 216, 55, 55, 90, 236, 19, 91, 109, 65, 86, 110, 14, 91, 99,
    39, 218, 8, 159, 64, 165, 16, 42, 195, 218, 162, 74, 210, 67, 72, 82, 81,
    116, 157, 55, 154, 246, 8, 78, 183, 108, 38, 161, 246, 109, 202, 77, 224,
    144, 59, 76, 98, 182, 139, 124, 155, 12, 9, 160, 218, 41, 13, 209, 76, 74,
    186, 59, 156, 132, 94, 130, 127, 12, 197, 36, 231, 143, 190, 247, 237, 89,
    228, 92, 19, 190, 172, 109, 253, 144, 140, 178, 83, 69, 219, 228, 43, 162,
    49, 210, 244, 4, 71, 93, 103, 116, 154, 151, 133, 2, 119, 228, 50, 177, 224,
    90, 10, 144, 143, 201, 87, 148, 184, 68, 57, 199, 224, 231, 53, 92, 34, 69,
    201, 135, 109, 204, 158, 220, 111, 105, 188, 173, 11, 110, 46, 165, 229,
    107, 197, 117, 74, 7, 74, 50, 112, 52, 120, 237, 70, 168, 56, 59, 16, 41,
    179, 177, 190, 60, 187, 222, 185, 201, 110, 77, 109, 167, 163, 43, 142, 85,
    206, 127, 33, 115, 79, 163, 140, 133, 224, 134, 24, 128, 233, 245, 142, 205,
    6, 86, 121, 250, 247, 44, 164, 178, 67, 224, 198, 226, 71, 55, 159, 149,
    205, 76, 255, 192, 114, 88, 5, 163, 59, 101, 174, 209, 34, 80, 139, 98, 50,
    79, 189, 80, 136, 124, 82, 247, 129, 191, 142, 52, 31, 140, 230, 15, 40, 62,
    124, 84, 113, 205, 143, 101, 199, 255, 192, 194, 82, 234, 241, 37, 58, 205,
    224, 177, 127, 52, 27, 160, 32, 30, 133, 193, 55, 29, 140, 54, 69, 70, 221,
    119, 125, 76, 2, 66, 226, 51, 29, 93, 82, 1, 134, 91, 5, 189, 19, 250, 237,
    113, 221, 110, 190, 129, 47, 204, 19, 48, 134, 81, 146, 76, 153, 212, 22,
    226, 165, 165, 164, 32, 29, 13, 7, 249, 190, 173, 153, 28, 22, 163, 36, 46,
    74, 105, 109, 77, 243, 118, 207, 155, 16, 101, 49, 42, 4, 98, 208, 160, 237,
    210, 168, 63, 227, 202, 28, 52, 200, 70, 185, 132, 82, 95, 81, 160, 117, 55,
    38, 120, 110, 206, 185, 8, 151, 8, 113, 168, 92, 90, 205, 115, 66, 171, 75,
    66, 166, 98, 166, 143, 18, 94, 63, 241, 203, 72, 79, 142, 8, 13, 148, 250,
    119, 55, 128, 119, 194, 185, 154, 230, 60, 139, 137, 210, 234, 167, 60, 199,
    216, 206, 236, 171, 182, 165, 174, 163, 55, 199, 204, 55, 5, 49, 83, 122,
    141, 147, 44, 248, 121, 254, 12, 239, 243, 92, 187, 21, 69, 212, 12, 54,
    204, 2, 36, 79, 106, 164, 99, 204, 209, 57, 56, 68, 175, 213, 74, 66, 42,
    162, 67, 189, 180, 48, 169, 57, 79, 26, 57, 232, 150, 155, 27, 185, 157,
    228, 76, 170, 10, 200, 234, 32, 41, 107, 234, 15, 77, 52, 89, 63, 206, 58,
    21, 210, 56, 229, 134, 248, 166, 131, 155, 9, 82, 119, 253, 216, 27, 217,
    198, 96, 45, 135, 40, 176, 169, 129, 105, 174, 251, 61, 213, 101, 91, 253,
    252, 58, 58, 204, 21, 157, 239, 47, 206, 114, 14, 247, 175, 170, 145, 105,
    100, 125, 59, 209, 59, 109, 12, 207, 182, 7, 61, 94, 66, 117, 22, 255, 208,
    143, 35, 230, 177, 95, 53, 203, 164, 161, 178, 108, 100, 45, 138, 167, 80,
    238, 114, 234, 202, 5, 216, 156, 139, 163, 128, 199, 158, 87, 242, 57, 102,
    127, 53, 18, 134, 44, 244, 1, 146, 161, 98, 214, 76, 191, 129, 253, 171,
    229, 114, 233, 123, 138, 83, 173, 232, 55, 88, 249, 236, 123, 36, 137, 100,
    253, 6, 228, 183, 34, 57, 242, 117, 32, 203, 42, 176, 67, 167, 0, 142, 165,
    109, 253, 101, 43, 171, 214, 204, 155, 102, 132, 0, 124, 211, 67, 196, 237,
    45, 131, 171, 192, 43, 131, 99, 191, 172, 101, 82, 64, 167, 46, 89, 210,
    149, 98, 207, 246, 162, 121, 170, 147, 20, 204, 131, 61, 225, 182, 144, 119,
    80, 76, 223, 4, 224, 75, 69, 157, 182, 121, 82, 67, 95, 201, 120, 205, 139,
    180, 129, 25, 88, 207, 169, 34, 150, 125, 64, 181, 237, 230, 132, 165, 145,
    102, 151, 171, 9, 189, 199, 128, 11, 198, 219, 193, 151, 0, 166, 108, 48, 9,
    254, 4, 247, 241, 159, 69, 160, 37, 77, 43, 235, 95, 104, 243, 13, 61, 22,
    232, 23, 53, 12, 237, 114, 95, 55, 42, 55, 208, 228, 149, 152, 5, 111, 176,
    101, 164, 57, 200, 97, 40, 105, 125, 172, 246, 241, 61, 219, 6, 249, 171,
    62, 55, 157, 44, 69, 95, 98, 158, 106, 236, 230, 80, 47, 120, 253, 160, 50,
    0, 54, 11, 41, 23, 48, 98, 1, 11, 34, 180, 230, 132, 100, 197, 39, 97, 186,
    187, 129, 172, 205, 51, 192, 163, 54, 11, 64, 135, 179, 135, 131, 29, 91,
    51, 62, 144, 105, 17, 140, 132, 207, 170, 53, 139, 176, 76, 54, 175, 149,
    63, 89, 82, 236, 33, 48, 112, 165, 1, 56, 247, 113, 128, 38, 156, 228, 191,
    98, 31, 192, 158, 45, 3, 173, 0, 98, 96, 94, 49, 127, 5, 205, 226, 154, 0,
    243, 15, 187, 215, 101, 66, 183, 56, 11, 108, 210, 93, 161, 235, 47, 116,
    48, 185, 60, 128, 180, 84, 225, 238, 197, 119, 53, 79, 14, 86, 179, 170,
    115, 115, 138, 157, 201, 26, 29, 58, 244, 131, 27, 70, 173, 229, 29, 211,
    84, 17, 222, 3, 60, 65, 105, 254, 54, 150, 12, 235, 143, 252, 21, 232, 185,
    7, 75, 129, 17, 105, 1, 233, 118, 76, 100, 24, 252, 240, 18, 196, 76, 241,
    3, 40, 172, 207, 151, 182, 148, 92, 115, 53, 103, 64, 186, 205, 136, 128,
    197, 202, 120, 109, 39, 62, 7, 211, 124, 90, 22, 105, 98, 196, 231, 102,
    119, 212, 240, 144, 253, 86, 202, 175, 223, 69, 35, 157, 81, 26, 45, 115,
    75, 88, 81, 220, 73, 207, 153, 250, 39, 166, 188, 225, 204, 100, 29, 134,
    63, 213, 187, 186, 247, 169, 113, 251, 220, 0, 243, 144, 93, 134, 216, 247,
    203, 185, 187, 137, 150, 19, 131, 241, 127, 52, 126, 247, 200, 221, 121,
    105, 246, 86, 161, 55, 29, 220, 44, 250, 49, 234, 206, 94, 162, 30, 239, 6,
    251, 126, 240, 206, 209, 136, 191, 185, 25, 225, 244, 132, 174, 14, 134, 30,
    226, 232, 168, 117, 193, 177, 127, 232, 6, 64, 7, 169, 45, 24, 220, 163,
    249, 180, 186, 4, 170, 185, 155, 196, 196, 117, 72, 6, 247, 175, 171, 175,
    95, 3, 7, 186, 255, 84, 186, 0, 166, 255, 7, 211, 191, 29, 248, 25, 3 };

#include <iostream>
#include <sstream>

void pure_lua_tableExt_open(lua_State* L)
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