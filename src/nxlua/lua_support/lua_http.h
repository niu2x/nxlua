#ifndef NXLUA_LUA_HTTP_H
#define NXLUA_LUA_HTTP_H

#include "http/send.h"

typedef int lua_Function;

namespace nxlua::http {

void lua_send(nxlua::http::request_t* request, int handler);

}; // namespace nxlua::http

#endif