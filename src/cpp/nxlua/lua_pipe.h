#ifndef NXLUA_LUA_PIPE_H
#define NXLUA_LUA_PIPE_H

#include "niu2x/pipe.h"

namespace nxlua::lua::pipe {
namespace filter = nx::pipe::filter;
extern std::string pipe(const std::string& sz, nx::pipe::filter_proxy_t filter);
}; // namespace nxlua::lua::pipe

#endif