#include "byte.h"

#include <filesystem>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <boost/endian/conversion.hpp>

#include "utils.h"
#include "nx_assert.h"

#define NAME byte

namespace nxlua {

#define BYTE_SERIALIZE(BITS)                                                   \
    static int byte_serialize##BITS(lua_State* L)                              \
    {                                                                          \
        uint##BITS##_t n = (uint##BITS##_t)lua_tonumber(L, -1);                \
        n = boost::endian::native_to_big<uint##BITS##_t>(n);                   \
        lua_pushlstring(L, (char*)(&n), sizeof(n));                            \
        return 1;                                                              \
    }

#define BYTE_DESERIALIZE(BITS)                                                 \
    static int byte_deserialize##BITS(lua_State* L)                            \
    {                                                                          \
        size_t len;                                                            \
        const char* ptr = lua_tolstring(L, -1, &len);                          \
        NX_ASSERT((len * 8) >= BITS,                                           \
            "no enough bytes to deserialize " stringify(BITS) " bit value");   \
        uint##BITS##_t n;                                                      \
        memcpy(&n, ptr, ((BITS) >> 3));                                        \
        n = boost::endian::big_to_native<uint##BITS##_t>(n);                   \
        lua_pushnumber(L, n);                                                  \
        return 1;                                                              \
    }

BYTE_SERIALIZE(8)
BYTE_SERIALIZE(16)
BYTE_SERIALIZE(32)
BYTE_SERIALIZE(64)
BYTE_DESERIALIZE(8)
BYTE_DESERIALIZE(16)
BYTE_DESERIALIZE(32)
BYTE_DESERIALIZE(64)
void lua_byte_open(lua_State* L)
{
    luaL_Reg reg[] = { { "serialize8", byte_serialize8 },
        { "serialize16", byte_serialize16 },
        { "serialize32", byte_serialize32 },
        { "serialize64", byte_serialize64 },

        { "deserialize8", byte_deserialize8 },
        { "deserialize16", byte_deserialize16 },
        { "deserialize32", byte_deserialize32 },
        { "deserialize64", byte_deserialize64 },

        { NULL, NULL } };
    luaL_register(L, stringify(NAME), reg);
}

} // namespace nxlua