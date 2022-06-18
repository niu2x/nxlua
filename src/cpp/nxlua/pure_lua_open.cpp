#include "pure_lua/PreFix.h"
#include "pure_lua/class.h"
#include "pure_lua/Image.h"
#include "pure_lua/mathExt.h"
#include "pure_lua/stringExt.h"
#include "pure_lua/tableExt.h"
#include "pure_lua/path_utils.h"
#include "pure_lua/appInit.h"
#include "pure_lua/print.h"
#include "pure_lua/F.h"
#include "pure_lua/welcome.h"
#include "pure_lua/re.h"
#include "pure_lua/lupa.h"
#include "pure_lua/dhttp.h"
#include "pure_lua/deferred.h"

void pure_lua_open(lua_State* L)
{
    pure_lua_PreFix_open(L);
    pure_lua_class_open(L);
    pure_lua_Image_open(L);
    pure_lua_mathExt_open(L);
    pure_lua_stringExt_open(L);
    pure_lua_tableExt_open(L);
    pure_lua_path_utils_open(L);
    pure_lua_appInit_open(L);
    pure_lua_print_open(L);
    pure_lua_F_open(L);
    pure_lua_welcome_open(L);
    pure_lua_re_open(L);
    pure_lua_lupa_open(L);
    pure_lua_dhttp_open(L);
    pure_lua_deferred_open(L);
}