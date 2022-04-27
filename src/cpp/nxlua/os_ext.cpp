#include "os_ext.h"

#include <filesystem>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "utils.h"

#define NAME os_ext

namespace nxlua {

static int os_ext_getcwd(lua_State* L)
{
    auto path = std::filesystem::current_path();
    lua_pushstring(L, path.c_str());
    return 1;
}

void lua_os_ext_open(lua_State* L)
{
    luaL_Reg reg[] = { { "getcwd", os_ext_getcwd }, { NULL, NULL } };
    luaL_register(L, stringify(NAME), reg);
}

} // namespace nxlua