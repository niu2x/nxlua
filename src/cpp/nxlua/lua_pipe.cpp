#include "lua_pipe.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "utils.h"

#include <sstream>

namespace nxlua::lua::pipe {

std::string pipe(const std::string& sz, nx::pipe::filter_proxy_t filter)
{
    std::istringstream is(sz);
    nx::pipe::source_t source(is);

    std::stringstream out;
    nx::pipe::sink_t sink(out);

    source | filter | sink;

    return out.str();
}

}; // namespace nxlua::lua::pipe