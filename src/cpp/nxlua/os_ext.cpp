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
    lua_pushstring(L, path.u8string().c_str());
    return 1;
}

static int os_ext_is_absolute(lua_State* L)
{
    auto* path_c = lua_tostring(L, -1);
    auto is_absolute = std::filesystem::path(path_c).is_absolute();
    lua_pushboolean(L, is_absolute);
    return 1;
}

static int os_ext_is_relative(lua_State* L)
{
    auto* path_c = lua_tostring(L, -1);
    auto is_absolute = std::filesystem::path(path_c).is_relative();
    lua_pushboolean(L, is_absolute);
    return 1;
}

void lua_os_ext_open(lua_State* L)
{
#define REG_FUNC_ENTRY(name) { #name, os_ext_##name },

    // clang-format off
    luaL_Reg reg[] = { 
        REG_FUNC_ENTRY(getcwd)
        REG_FUNC_ENTRY(is_absolute)
        REG_FUNC_ENTRY(is_relative)
        { NULL, NULL } 
    };
    // clang-format on

    luaL_register(L, stringify(NAME), reg);
}

} // namespace nxlua