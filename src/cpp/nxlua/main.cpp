#include <string>
#include <iostream>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#error "test-pr"

extern "C" {
LUALIB_API int luaopen_bit(lua_State* L);
extern int luaopen_cjson(lua_State* l);
}

#include <tolua++.h>

TOLUA_API int tolua_image_open(lua_State* tolua_S);
extern void pure_lua_open(lua_State* L);
extern void dotty(lua_State* L);
extern void tolua_libs_open(lua_State* L);

#include "image/image.h"

struct params_t {
    char* input_file;
};

static void params_parse(struct params_t* self, int argc, char* argv[])
{
    self->input_file = nullptr;
    if (argc >= 2) {
        self->input_file = argv[1];
    }
}

static void run_interactive(lua_State* L) { dotty(L); }
static void run(lua_State* L, const char* input_file)
{
    if (luaL_dofile(L, input_file)) {
        std::cerr << lua_tostring(L, -1) << std::endl;
    }
}

static void open_libs(lua_State* L)
{
    luaL_openlibs(L);
    luaopen_bit(L);
    luaopen_cjson(L);
    tolua_libs_open(L);
    pure_lua_open(L);
}

int main(int argc, char* argv[], char* env[])
{

    struct params_t params;
    params_parse(&params, argc, argv);

    auto L = luaL_newstate();
    open_libs(L);

    bool interactive = !params.input_file;

    if (interactive)
        run_interactive(L);
    else
        run(L, params.input_file);

    lua_close(L);

    // nxlua::image_t image;
    // image.load("./1.png");

    // nxlua::image_t image2;
    // image2.resize(128, 128);

    // nxlua::image_t::resample_subimage(&image, &image2, 0, 0, image.width(),
    // image.height(), 0);

    // image2.save("./2.png");

    return 0;
}
