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
    const char* input_file;
    bool version;
    bool help;
};

lua_State* main_L = nullptr;

static int params_parse(struct params_t* self, int argc, char* argv[])
{
    int nr_consumed_args = 1;
    for (; self->input_file == nullptr && nr_consumed_args < argc;
         nr_consumed_args++) {
        const char* arg = argv[nr_consumed_args];
        if (arg[0] == '-') {
            if (!strcmp(arg, "-v") || !strcmp(arg, "--version")) {
                self->version = true;
                continue;
            }

            if (!strcmp(arg, "-h") || !strcmp(arg, "--help")) {
                self->help = true;
                continue;
            }

        } else {
            self->input_file = arg;
        }
    }
    return nr_consumed_args;
}

static void show_help() { std::cout << "NXLUA Help TODO" << std::endl; }

static void show_version()
{
    std::cout << stringify(NXLUA_PROJECT_NAME) << "("
              << stringify(NXLUA_PROJECT_VERSION) << "-"
              << stringify(NXLUA_GIT_HASH) << ")" << std::endl;
}

static void run_interactive(lua_State* L)
{
    show_version();
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
    memset(&params, 0, sizeof(params));
    int nr_consumed_args = params_parse(&params, argc, argv);

    auto L = luaL_newstate();

    save_argv(L, argc - nr_consumed_args, argv + nr_consumed_args);

    open_libs(L);
    main_L = L;

    nxlua::http::setup();

    // auto req = std::make_unique<nxlua::http::request_t>();
    // req->set_url("http://www.baidu.com");
    // nxlua::http::send(std::move(req), [](auto resp){
    //     printf("resp %s\n", resp->body().c_str());
    // });

    bool interactive = !params.input_file;

    if (params.version) {
        show_version();
    } else if (params.help) {
        show_help();
    } else if (interactive) {
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