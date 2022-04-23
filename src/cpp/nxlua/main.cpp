extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <string>

extern void pure_lua_open(lua_State* L);

extern "C" {
extern void dotty(lua_State* L);
LUALIB_API int luaopen_bit(lua_State* L);
}

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
    luaL_dofile(L, input_file);
}

static void open_libs(lua_State* L)
{
    luaL_openlibs(L);
    luaopen_bit(L);
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

    return 0;
}