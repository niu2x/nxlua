/*
** Lua binding: lua_pipe
** Generated automatically by tolua++-1.0.93 on Thu Apr 28 14:01:46 2022.
*/

#ifndef __cplusplus
    #include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_lua_pipe_open(lua_State* tolua_S);

#include "lua_pipe.h"
#include "nxlua/pipe.h"
using namespace nxlua::lua;
using namespace nx::pipe::filter;

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_pipe__filter__unbase64_t(lua_State* tolua_S)
{
    pipe::filter::unbase64_t* self
        = (pipe::filter::unbase64_t*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pipe__filter__base64_t(lua_State* tolua_S)
{
    pipe::filter::base64_t* self
        = (pipe::filter::base64_t*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}
#endif

/* function to register type */
static void tolua_reg_types(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "pipe::filter::unbase64_t");
    tolua_usertype(tolua_S, "pipe::filter::base64_t");
}

/* method: new of class  pipe::filter::base64_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_base64_t_new00
static int tolua_lua_pipe_pipe_filter_base64_t_new00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::base64_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            pipe::filter::base64_t* tolua_ret
                = (pipe::filter::base64_t*)Mtolua_new(
                    (pipe::filter::base64_t)());
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::base64_t");
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'new'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  pipe::filter::base64_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_base64_t_new00_local
static int tolua_lua_pipe_pipe_filter_base64_t_new00_local(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::base64_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            pipe::filter::base64_t* tolua_ret
                = (pipe::filter::base64_t*)Mtolua_new(
                    (pipe::filter::base64_t)());
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::base64_t");
            tolua_register_gc(tolua_S, lua_gettop(tolua_S));
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'new'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  pipe::filter::base64_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_base64_t_delete00
static int tolua_lua_pipe_pipe_filter_base64_t_delete00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "pipe::filter::base64_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        pipe::filter::base64_t* self
            = (pipe::filter::base64_t*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'delete'", NULL);
    #endif
        Mtolua_delete(self);
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'delete'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  pipe::filter::unbase64_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_unbase64_t_new00
static int tolua_lua_pipe_pipe_filter_unbase64_t_new00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(
            tolua_S, 1, "pipe::filter::unbase64_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            pipe::filter::unbase64_t* tolua_ret
                = (pipe::filter::unbase64_t*)Mtolua_new(
                    (pipe::filter::unbase64_t)());
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::unbase64_t");
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'new'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  pipe::filter::unbase64_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_unbase64_t_new00_local
static int tolua_lua_pipe_pipe_filter_unbase64_t_new00_local(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(
            tolua_S, 1, "pipe::filter::unbase64_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            pipe::filter::unbase64_t* tolua_ret
                = (pipe::filter::unbase64_t*)Mtolua_new(
                    (pipe::filter::unbase64_t)());
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::unbase64_t");
            tolua_register_gc(tolua_S, lua_gettop(tolua_S));
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'new'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  pipe::filter::unbase64_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_unbase64_t_delete00
static int tolua_lua_pipe_pipe_filter_unbase64_t_delete00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "pipe::filter::unbase64_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        pipe::filter::unbase64_t* self
            = (pipe::filter::unbase64_t*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'delete'", NULL);
    #endif
        Mtolua_delete(self);
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'delete'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: pipe::pipe */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_pipe00
static int tolua_lua_pipe_pipe_pipe00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_iscppstring(tolua_S, 1, 0, &tolua_err)
        || (tolua_isvaluenil(tolua_S, 2, &tolua_err)
            || !tolua_isusertype(
                tolua_S, 2, "pipe::filter::base64_t", 0, &tolua_err))
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const std::string sz
            = ((const std::string)tolua_tocppstring(tolua_S, 1, 0));
        pipe::filter::base64_t* filter
            = ((pipe::filter::base64_t*)tolua_tousertype(tolua_S, 2, 0));
        {
            std::string tolua_ret = (std::string)pipe::pipe(sz, *filter);
            tolua_pushcppstring(tolua_S, (const char*)tolua_ret);
            tolua_pushcppstring(tolua_S, (const char*)sz);
        }
    }
    return 2;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'pipe'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_lua_pipe_open(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    tolua_reg_types(tolua_S);
    tolua_module(tolua_S, NULL, 0);
    tolua_beginmodule(tolua_S, NULL);
    tolua_module(tolua_S, "pipe", 0);
    tolua_beginmodule(tolua_S, "pipe");
    tolua_module(tolua_S, "filter", 0);
    tolua_beginmodule(tolua_S, "filter");
#ifdef __cplusplus
    tolua_cclass(tolua_S, "base64_t", "pipe::filter::base64_t", "",
        tolua_collect_pipe__filter__base64_t);
#else
    tolua_cclass(tolua_S, "base64_t", "pipe::filter::base64_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "base64_t");
    tolua_function(tolua_S, "new", tolua_lua_pipe_pipe_filter_base64_t_new00);
    tolua_function(
        tolua_S, "new_local", tolua_lua_pipe_pipe_filter_base64_t_new00_local);
    tolua_function(
        tolua_S, ".call", tolua_lua_pipe_pipe_filter_base64_t_new00_local);
    tolua_function(
        tolua_S, "delete", tolua_lua_pipe_pipe_filter_base64_t_delete00);
    tolua_endmodule(tolua_S);
#ifdef __cplusplus
    tolua_cclass(tolua_S, "unbase64_t", "pipe::filter::unbase64_t", "",
        tolua_collect_pipe__filter__unbase64_t);
#else
    tolua_cclass(tolua_S, "unbase64_t", "pipe::filter::unbase64_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "unbase64_t");
    tolua_function(tolua_S, "new", tolua_lua_pipe_pipe_filter_unbase64_t_new00);
    tolua_function(tolua_S, "new_local",
        tolua_lua_pipe_pipe_filter_unbase64_t_new00_local);
    tolua_function(
        tolua_S, ".call", tolua_lua_pipe_pipe_filter_unbase64_t_new00_local);
    tolua_function(
        tolua_S, "delete", tolua_lua_pipe_pipe_filter_unbase64_t_delete00);
    tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    tolua_function(tolua_S, "pipe", tolua_lua_pipe_pipe_pipe00);
    tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    return 1;
}

#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
TOLUA_API int luaopen_lua_pipe(lua_State* tolua_S)
{
    return tolua_lua_pipe_open(tolua_S);
};
#endif
