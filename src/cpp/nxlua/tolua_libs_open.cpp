#include <tolua++.h>
TOLUA_API int tolua_image_open(lua_State* tolua_S);

void tolua_libs_open(lua_State* L) { tolua_image_open(L); }