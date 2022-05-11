#include "os_ext.h"

#include <filesystem>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "utils.h"

namespace nxlua {


void lua_version_open(lua_State* L)
{
    lua_newtable(L);

    lua_pushnumber(L, NXLUA_PROJECT_VERSION_MAJOR);
    lua_setfield(L, -2, "major");

    lua_pushnumber(L, NXLUA_PROJECT_VERSION_MINOR);
    lua_setfield(L, -2, "minor");

    lua_pushnumber(L, NXLUA_PROJECT_VERSION_PATCH);
    lua_setfield(L, -2, "patch");

    lua_setglobal(L, "NXLUA_VERSION");
}


} // namespace nxlua