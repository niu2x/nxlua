#include <tolua++.h>
TOLUA_API int tolua_image_open(lua_State* tolua_S);
TOLUA_API int tolua_lua_pipe_open(lua_State* tolua_S);
TOLUA_API int tolua_lua_http_open(lua_State* tolua_S);

void tolua_libs_open(lua_State* L)
{
    tolua_image_open(L);
    tolua_lua_pipe_open(L);
    tolua_lua_http_open(L);
}