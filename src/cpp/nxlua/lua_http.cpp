#include "lua_http.h"
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <tolua++.h>

extern lua_State* main_L;
;

namespace nxlua::http {

void lua_send(request_t* request, int handler)
{
    auto L = main_L;

    lua_pushvalue(L, handler);
    auto func_id = luaL_ref(L, LUA_REGISTRYINDEX);

    auto req = std::make_unique<request_t>();
    *req = std::move(*request);

    send(std::move(req), [L, func_id](auto resp) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, func_id);

        response_t* response
            = (http::response_t*)Mtolua_new((http::response_t)());
        *response = std::move(*resp);
        tolua_pushusertype(L, (void*)response, "http::response_t");
        tolua_register_gc(L, lua_gettop(L));
        lua_call(L, 1, 0);

        luaL_unref(L, LUA_REGISTRYINDEX, func_id);
    });
}

}; // namespace nxlua::http
