// copy from lua.c

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>

#define lua_c

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <linenoise.hpp>

#include "utils.h"

static const char* progname = stringify(NXLUA_PROJECT_NAME);

static void lstop(lua_State* L, lua_Debug* ar)
{
    (void)ar; /* unused arg. */
    lua_sethook(L, NULL, 0, 0);
    luaL_error(L, "interrupted!");
}

static lua_State* globalL = 0;

static void l_message(const char* pname, const char* msg)
{
    if (pname)
        fprintf(stderr, "%s: ", pname);
    fprintf(stderr, "%s\n", msg);
    fflush(stderr);
}

static void laction(int i)
{
    signal(i, SIG_DFL); /* if another SIGINT happens before lstop,
                                terminate process (default action) */
    lua_sethook(globalL, lstop, LUA_MASKCALL | LUA_MASKRET | LUA_MASKCOUNT, 1);
}

static int incomplete(lua_State* L, int status)
{
    if (status == LUA_ERRSYNTAX) {
        size_t lmsg;
        const char* msg = lua_tolstring(L, -1, &lmsg);
        const char* tp = msg + lmsg - (sizeof(LUA_QL("<eof>")) - 1);
        if (strstr(msg, LUA_QL("<eof>")) == tp) {
            lua_pop(L, 1);
            return 1;
        }
    }
    return 0; /* else... */
}

static const char* get_prompt(lua_State* L, int firstline)
{
    const char* p;
    lua_getfield(L, LUA_GLOBALSINDEX, firstline ? "_PROMPT" : "_PROMPT2");
    p = lua_tostring(L, -1);
    if (p == NULL)
        p = (firstline ? LUA_PROMPT : LUA_PROMPT2);
    lua_pop(L, 1); /* remove global */
    return p;
}

static int pushline(lua_State* L, int firstline)
{

    char* b = 0;
    size_t l;
    const char* prmt = get_prompt(L, firstline);

    std::string line;
    auto quit = linenoise::Readline(prmt, line);

    if (quit)
        return 0;
    b = (char*)line.c_str();

    l = strlen(b);
    if (l > 0 && b[l - 1] == '\n') /* line ends with newline? */
        b[l - 1] = '\0'; /* remove it */
    if (firstline && b[0] == '=') /* first line starts with `=' ? */
        lua_pushfstring(L, "return %s", b + 1); /* change it to `return' */
    else
        lua_pushstring(L, b);
    lua_freeline(L, b);
    return 1;
}

static int loadline(lua_State* L)
{
    int status;
    lua_settop(L, 0);
    if (!pushline(L, 1))
        return -1; /* no input */
    for (;;) { /* repeat until gets a complete line */
        status = luaL_loadbuffer(
            L, lua_tostring(L, 1), lua_strlen(L, 1), "=stdin");
        if (!incomplete(L, status))
            break; /* cannot try to add lines? */
        if (!pushline(L, 0)) /* no more input? */
            return -1;
        lua_pushliteral(L, "\n"); /* add a new line... */
        lua_insert(L, -2); /* ...between the two lines */
        lua_concat(L, 3); /* join them */
    }
    linenoise::AddHistory(lua_tostring(L, 1));
    lua_remove(L, 1); /* remove line */
    return status;
}

static int report(lua_State* L, int status)
{
    if (status && !lua_isnil(L, -1)) {
        const char* msg = lua_tostring(L, -1);
        if (msg == NULL)
            msg = "(error object is not a string)";
        l_message(progname, msg);
        lua_pop(L, 1);
    }
    return status;
}

static int traceback(lua_State* L)
{
    if (!lua_isstring(L, 1)) /* 'message' not a string? */
        return 1; /* keep it intact */
    lua_getfield(L, LUA_GLOBALSINDEX, "debug");
    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        return 1;
    }
    lua_getfield(L, -1, "traceback");
    if (!lua_isfunction(L, -1)) {
        lua_pop(L, 2);
        return 1;
    }
    lua_pushvalue(L, 1); /* pass error message */
    lua_pushinteger(L, 2); /* skip this function and traceback */
    lua_call(L, 2, 1); /* call debug.traceback */
    return 1;
}

static int docall(lua_State* L, int narg, int clear)
{
    int status;
    int base = lua_gettop(L) - narg; /* function index */
    lua_pushcfunction(L, traceback); /* push traceback function */
    lua_insert(L, base); /* put it under chunk and args */
    signal(SIGINT, laction);
    status = lua_pcall(L, narg, (clear ? 0 : LUA_MULTRET), base);
    signal(SIGINT, SIG_DFL);
    lua_remove(L, base); /* remove traceback function */
    /* force a complete garbage collection in case of errors */
    if (status != 0)
        lua_gc(L, LUA_GCCOLLECT, 0);
    return status;
}

void dotty(lua_State* L)
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

    globalL = L;
    int status;
    const char* oldprogname = progname;
    progname = NULL;
    while ((status = loadline(L)) != -1) {
        if (status == 0)
            status = docall(L, 0, 0);
        report(L, status);
        if (status == 0 && lua_gettop(L) > 0) { /* any result to print? */
            lua_getglobal(L, "print");
            lua_insert(L, 1);
            if (lua_pcall(L, lua_gettop(L) - 1, 0, 0) != 0)
                l_message(progname,
                    lua_pushfstring(L, "error calling " LUA_QL("print") " (%s)",
                        lua_tostring(L, -1)));
        }
    }
    lua_settop(L, 0); /* clear stack */
    fputs("\n", stdout);
    fflush(stdout);
    progname = oldprogname;
}