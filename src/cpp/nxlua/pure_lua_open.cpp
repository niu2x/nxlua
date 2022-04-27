#include "pure_lua/PreFix.h"
#include "pure_lua/class.h"
#include "pure_lua/Image.h"
#include "pure_lua/mathExt.h"
#include "pure_lua/stringExt.h"
#include "pure_lua/tableExt.h"
#include "pure_lua/appInit.h"

void pure_lua_open(lua_State* L)
{
    pure_lua_PreFix_open(L);
    pure_lua_class_open(L);
    pure_lua_Image_open(L);
    pure_lua_mathExt_open(L);
    pure_lua_stringExt_open(L);
    pure_lua_tableExt_open(L);
    pure_lua_appInit_open(L);
}