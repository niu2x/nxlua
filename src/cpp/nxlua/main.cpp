extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <linenoise.hpp>

#include <string>

#define stringify(s)   __stringify(s)
#define __stringify(s) #s

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

static void run_interactive(lua_State* L)
{
    linenoise::SetCompletionCallback(
        [](const char* editBuffer, std::vector<std::string>& completions) {
            // if (editBuffer[0] == 'h') {
            //     completions.push_back("hello");
            //     completions.push_back("hello there");
            // }
        });

    linenoise::SetMultiLine(true);
    linenoise::SetHistoryMaxLen(1024);

    while (true) {
        std::string line;
        auto quit = linenoise::Readline("> ", line);

        if (quit) {
            break;
        }

        auto ret = luaL_dostring(L, line.c_str());
        if (ret != 0) {
            auto msg = lua_tostring(L, -1);
            std::cerr << msg;
        }

        linenoise::AddHistory(line.c_str());
    }
}
static void run(lua_State* L, const char* input_file)
{
    luaL_dofile(L, input_file);
}

static void open_libs(lua_State* L) { luaL_openlibs(L); }

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