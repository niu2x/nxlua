#include <string>
#include <iostream>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <luv/src/luv.h>
}

extern "C" {
LUALIB_API int luaopen_bit(lua_State* L);
extern int luaopen_cjson(lua_State* l);
extern int luaopen_lpeg(lua_State* L);
}

#include <tolua++.h>
#include "lfs.h"

TOLUA_API int tolua_image_open(lua_State* tolua_S);
extern void pure_lua_open(lua_State* L);
extern void dotty(lua_State* L);
extern void tolua_libs_open(lua_State* L);

#include "image/image.h"
#include "os_ext.h"
#include "version.h"
#include "byte.h"
#include "thread/thread_group.h"
#include "thread/io_context.h"
#include "utils.h"
#include "http/send.h"

struct params_t {
    char* input_file;
};

lua_State* main_L = nullptr;

static void params_parse(struct params_t* self, int argc, char* argv[])
{
    self->input_file = nullptr;
    if (argc >= 2) {
        self->input_file = argv[1];
    }
}

static void run_interactive(lua_State* L)
{
    std::cout << stringify(NXLUA_PROJECT_NAME) << "("
              << stringify(NXLUA_PROJECT_VERSION) << "-"
              << stringify(NXLUA_GIT_HASH) << ")" << std::endl;
    dotty(L);
}

static void save_argv(lua_State* L, int argc, char* argv[])
{
    lua_newtable(L);
    lua_newtable(L);

    for (int i = 0; i < argc; i++) {
        lua_pushstring(L, argv[i]);
        lua_rawseti(L, -2, i + 1);
    }

    lua_setfield(L, -2, "argv");
    lua_setglobal(L, "sys");
}

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
    luaopen_luv(L);
    lua_setglobal(L, "luv");
    luaopen_lfs(L);
    luaopen_lpeg(L);
    nxlua::lua_os_ext_open(L);
    nxlua::lua_byte_open(L);
    nxlua::lua_version_open(L);
    pure_lua_open(L);
}

int main(int argc, char* argv[], char* env[])
{

    struct params_t params;
    params_parse(&params, argc, argv);

    auto L = luaL_newstate();

    save_argv(L, argc - 1, argv + 1);

    open_libs(L);
    main_L = L;

    nxlua::http::setup();

    // auto req = std::make_unique<nxlua::http::request_t>();
    // req->set_url("http://www.baidu.com");
    // nxlua::http::send(std::move(req), [](auto resp){
    //     printf("resp %s\n", resp->body().c_str());
    // });

    bool interactive = !params.input_file;

    if (interactive) {
        run_interactive(L);
    } else
        run(L, params.input_file);

    nxlua::http::cleanup();

    main_L = nullptr;
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