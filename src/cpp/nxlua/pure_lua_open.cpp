#include "pure_lua/class.h"
#include "pure_lua/Image.h"

void pure_lua_open(lua_State* L)
{
    pure_lua_class_open(L);
    pure_lua_Image_open(L);
}