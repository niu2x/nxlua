/*
** Lua binding: lua_pipe
** Generated automatically by tolua++-1.0.93 on Thu Apr 28 22:25:42 2022.
*/

#ifndef __cplusplus
    #include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_lua_pipe_open(lua_State* tolua_S);

#include "lua_pipe.h"
#include "niu2x/pipe.h"
using namespace nxlua::lua;
using namespace nx::pipe::filter;

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_pipe__filter__encrypt_t(lua_State* tolua_S)
{
    pipe::filter::encrypt_t* self
        = (pipe::filter::encrypt_t*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pipe__filter__cut_t(lua_State* tolua_S)
{
    pipe::filter::cut_t* self
        = (pipe::filter::cut_t*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pipe__filter__upper_t(lua_State* tolua_S)
{
    pipe::filter::upper_t* self
        = (pipe::filter::upper_t*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pipe__filter__hex_t(lua_State* tolua_S)
{
    pipe::filter::hex_t* self
        = (pipe::filter::hex_t*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pipe__filter__decrypt_t(lua_State* tolua_S)
{
    pipe::filter::decrypt_t* self
        = (pipe::filter::decrypt_t*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pipe__filter__unzlib_t(lua_State* tolua_S)
{
    pipe::filter::unzlib_t* self
        = (pipe::filter::unzlib_t*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pipe__filter__zlib_t(lua_State* tolua_S)
{
    pipe::filter::zlib_t* self
        = (pipe::filter::zlib_t*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pipe__filter__unhex_t(lua_State* tolua_S)
{
    pipe::filter::unhex_t* self
        = (pipe::filter::unhex_t*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pipe__filter__digest_t(lua_State* tolua_S)
{
    pipe::filter::digest_t* self
        = (pipe::filter::digest_t*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}

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

static int tolua_collect_pipe__filter__lower_t(lua_State* tolua_S)
{
    pipe::filter::lower_t* self
        = (pipe::filter::lower_t*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}
#endif

/* function to register type */
static void tolua_reg_types(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "pipe::filter::encrypt_t");
    tolua_usertype(tolua_S, "pipe::filter::cut_t");
    tolua_usertype(tolua_S, "pipe::filter::upper_t");
    tolua_usertype(tolua_S, "pipe::filter::hex_t");
    tolua_usertype(tolua_S, "pipe::filter::decrypt_t");
    tolua_usertype(tolua_S, "pipe::filter::unzlib_t");
    tolua_usertype(tolua_S, "pipe::filter::zlib_t");
    tolua_usertype(tolua_S, "pipe::filter::unhex_t");
    tolua_usertype(tolua_S, "pipe::filter::digest_t");
    tolua_usertype(tolua_S, "pipe::filter::unbase64_t");
    tolua_usertype(tolua_S, "pipe::filter::base64_t");
    tolua_usertype(tolua_S, "pipe::filter::lower_t");
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

/* method: new of class  pipe::filter::lower_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_lower_t_new00
static int tolua_lua_pipe_pipe_filter_lower_t_new00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::lower_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            pipe::filter::lower_t* tolua_ret
                = (pipe::filter::lower_t*)Mtolua_new((pipe::filter::lower_t)());
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::lower_t");
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

/* method: new_local of class  pipe::filter::lower_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_lower_t_new00_local
static int tolua_lua_pipe_pipe_filter_lower_t_new00_local(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::lower_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            pipe::filter::lower_t* tolua_ret
                = (pipe::filter::lower_t*)Mtolua_new((pipe::filter::lower_t)());
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::lower_t");
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

/* method: delete of class  pipe::filter::lower_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_lower_t_delete00
static int tolua_lua_pipe_pipe_filter_lower_t_delete00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "pipe::filter::lower_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        pipe::filter::lower_t* self
            = (pipe::filter::lower_t*)tolua_tousertype(tolua_S, 1, 0);
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

/* method: new of class  pipe::filter::upper_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_upper_t_new00
static int tolua_lua_pipe_pipe_filter_upper_t_new00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::upper_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            pipe::filter::upper_t* tolua_ret
                = (pipe::filter::upper_t*)Mtolua_new((pipe::filter::upper_t)());
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::upper_t");
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

/* method: new_local of class  pipe::filter::upper_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_upper_t_new00_local
static int tolua_lua_pipe_pipe_filter_upper_t_new00_local(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::upper_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            pipe::filter::upper_t* tolua_ret
                = (pipe::filter::upper_t*)Mtolua_new((pipe::filter::upper_t)());
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::upper_t");
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

/* method: delete of class  pipe::filter::upper_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_upper_t_delete00
static int tolua_lua_pipe_pipe_filter_upper_t_delete00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "pipe::filter::upper_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        pipe::filter::upper_t* self
            = (pipe::filter::upper_t*)tolua_tousertype(tolua_S, 1, 0);
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

/* method: new of class  pipe::filter::hex_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_hex_t_new00
static int tolua_lua_pipe_pipe_filter_hex_t_new00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::hex_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            pipe::filter::hex_t* tolua_ret
                = (pipe::filter::hex_t*)Mtolua_new((pipe::filter::hex_t)());
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::hex_t");
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

/* method: new_local of class  pipe::filter::hex_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_hex_t_new00_local
static int tolua_lua_pipe_pipe_filter_hex_t_new00_local(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::hex_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            pipe::filter::hex_t* tolua_ret
                = (pipe::filter::hex_t*)Mtolua_new((pipe::filter::hex_t)());
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::hex_t");
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

/* method: delete of class  pipe::filter::hex_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_hex_t_delete00
static int tolua_lua_pipe_pipe_filter_hex_t_delete00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "pipe::filter::hex_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        pipe::filter::hex_t* self
            = (pipe::filter::hex_t*)tolua_tousertype(tolua_S, 1, 0);
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

/* method: new of class  pipe::filter::unhex_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_unhex_t_new00
static int tolua_lua_pipe_pipe_filter_unhex_t_new00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::unhex_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            pipe::filter::unhex_t* tolua_ret
                = (pipe::filter::unhex_t*)Mtolua_new((pipe::filter::unhex_t)());
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::unhex_t");
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

/* method: new_local of class  pipe::filter::unhex_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_unhex_t_new00_local
static int tolua_lua_pipe_pipe_filter_unhex_t_new00_local(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::unhex_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            pipe::filter::unhex_t* tolua_ret
                = (pipe::filter::unhex_t*)Mtolua_new((pipe::filter::unhex_t)());
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::unhex_t");
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

/* method: delete of class  pipe::filter::unhex_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_unhex_t_delete00
static int tolua_lua_pipe_pipe_filter_unhex_t_delete00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "pipe::filter::unhex_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        pipe::filter::unhex_t* self
            = (pipe::filter::unhex_t*)tolua_tousertype(tolua_S, 1, 0);
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

/* method: new of class  pipe::filter::cut_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_cut_t_new00
static int tolua_lua_pipe_pipe_filter_cut_t_new00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::cut_t", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        unsigned char c = ((unsigned char)tolua_tonumber(tolua_S, 2, 0));
        {
            pipe::filter::cut_t* tolua_ret
                = (pipe::filter::cut_t*)Mtolua_new((pipe::filter::cut_t)(c));
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::cut_t");
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

/* method: new_local of class  pipe::filter::cut_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_cut_t_new00_local
static int tolua_lua_pipe_pipe_filter_cut_t_new00_local(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::cut_t", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        unsigned char c = ((unsigned char)tolua_tonumber(tolua_S, 2, 0));
        {
            pipe::filter::cut_t* tolua_ret
                = (pipe::filter::cut_t*)Mtolua_new((pipe::filter::cut_t)(c));
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::cut_t");
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

/* method: delete of class  pipe::filter::cut_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_cut_t_delete00
static int tolua_lua_pipe_pipe_filter_cut_t_delete00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "pipe::filter::cut_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        pipe::filter::cut_t* self
            = (pipe::filter::cut_t*)tolua_tousertype(tolua_S, 1, 0);
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

/* method: new of class  pipe::filter::zlib_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_zlib_t_new00
static int tolua_lua_pipe_pipe_filter_zlib_t_new00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::zlib_t", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        int level = ((int)tolua_tonumber(tolua_S, 2, 0));
        {
            pipe::filter::zlib_t* tolua_ret = (pipe::filter::zlib_t*)Mtolua_new(
                (pipe::filter::zlib_t)(level));
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::zlib_t");
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

/* method: new_local of class  pipe::filter::zlib_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_zlib_t_new00_local
static int tolua_lua_pipe_pipe_filter_zlib_t_new00_local(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::zlib_t", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        int level = ((int)tolua_tonumber(tolua_S, 2, 0));
        {
            pipe::filter::zlib_t* tolua_ret = (pipe::filter::zlib_t*)Mtolua_new(
                (pipe::filter::zlib_t)(level));
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::zlib_t");
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

/* method: delete of class  pipe::filter::zlib_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_zlib_t_delete00
static int tolua_lua_pipe_pipe_filter_zlib_t_delete00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "pipe::filter::zlib_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        pipe::filter::zlib_t* self
            = (pipe::filter::zlib_t*)tolua_tousertype(tolua_S, 1, 0);
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

/* method: new of class  pipe::filter::unzlib_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_unzlib_t_new00
static int tolua_lua_pipe_pipe_filter_unzlib_t_new00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::unzlib_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            pipe::filter::unzlib_t* tolua_ret
                = (pipe::filter::unzlib_t*)Mtolua_new(
                    (pipe::filter::unzlib_t)());
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::unzlib_t");
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

/* method: new_local of class  pipe::filter::unzlib_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_unzlib_t_new00_local
static int tolua_lua_pipe_pipe_filter_unzlib_t_new00_local(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::unzlib_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            pipe::filter::unzlib_t* tolua_ret
                = (pipe::filter::unzlib_t*)Mtolua_new(
                    (pipe::filter::unzlib_t)());
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::unzlib_t");
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

/* method: delete of class  pipe::filter::unzlib_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_unzlib_t_delete00
static int tolua_lua_pipe_pipe_filter_unzlib_t_delete00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "pipe::filter::unzlib_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        pipe::filter::unzlib_t* self
            = (pipe::filter::unzlib_t*)tolua_tousertype(tolua_S, 1, 0);
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

/* method: new of class  pipe::filter::digest_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_digest_t_new00
static int tolua_lua_pipe_pipe_filter_digest_t_new00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::digest_t", 0, &tolua_err)
        || !tolua_isstring(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const char* algorithm = ((const char*)tolua_tostring(tolua_S, 2, 0));
        {
            pipe::filter::digest_t* tolua_ret
                = (pipe::filter::digest_t*)Mtolua_new(
                    (pipe::filter::digest_t)(algorithm));
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::digest_t");
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

/* method: new_local of class  pipe::filter::digest_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_digest_t_new00_local
static int tolua_lua_pipe_pipe_filter_digest_t_new00_local(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::digest_t", 0, &tolua_err)
        || !tolua_isstring(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const char* algorithm = ((const char*)tolua_tostring(tolua_S, 2, 0));
        {
            pipe::filter::digest_t* tolua_ret
                = (pipe::filter::digest_t*)Mtolua_new(
                    (pipe::filter::digest_t)(algorithm));
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::digest_t");
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

/* method: delete of class  pipe::filter::digest_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_digest_t_delete00
static int tolua_lua_pipe_pipe_filter_digest_t_delete00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "pipe::filter::digest_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        pipe::filter::digest_t* self
            = (pipe::filter::digest_t*)tolua_tousertype(tolua_S, 1, 0);
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

/* method: new of class  pipe::filter::encrypt_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_encrypt_t_new00
static int tolua_lua_pipe_pipe_filter_encrypt_t_new00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::encrypt_t", 0, &tolua_err)
        || !tolua_isstring(tolua_S, 2, 0, &tolua_err)
        || !tolua_isstring(tolua_S, 3, 0, &tolua_err)
        || !tolua_isstring(tolua_S, 4, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 5, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const char* algorithm = ((const char*)tolua_tostring(tolua_S, 2, 0));
        unsigned const char* key
            = ((unsigned const char*)tolua_tostring(tolua_S, 3, 0));
        unsigned const char* iv
            = ((unsigned const char*)tolua_tostring(tolua_S, 4, 0));
        {
            pipe::filter::encrypt_t* tolua_ret
                = (pipe::filter::encrypt_t*)Mtolua_new(
                    (pipe::filter::encrypt_t)(algorithm, key, iv));
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::encrypt_t");
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

/* method: new_local of class  pipe::filter::encrypt_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_encrypt_t_new00_local
static int tolua_lua_pipe_pipe_filter_encrypt_t_new00_local(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::encrypt_t", 0, &tolua_err)
        || !tolua_isstring(tolua_S, 2, 0, &tolua_err)
        || !tolua_isstring(tolua_S, 3, 0, &tolua_err)
        || !tolua_isstring(tolua_S, 4, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 5, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const char* algorithm = ((const char*)tolua_tostring(tolua_S, 2, 0));
        unsigned const char* key
            = ((unsigned const char*)tolua_tostring(tolua_S, 3, 0));
        unsigned const char* iv
            = ((unsigned const char*)tolua_tostring(tolua_S, 4, 0));
        {
            pipe::filter::encrypt_t* tolua_ret
                = (pipe::filter::encrypt_t*)Mtolua_new(
                    (pipe::filter::encrypt_t)(algorithm, key, iv));
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::encrypt_t");
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

/* method: delete of class  pipe::filter::encrypt_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_encrypt_t_delete00
static int tolua_lua_pipe_pipe_filter_encrypt_t_delete00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "pipe::filter::encrypt_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        pipe::filter::encrypt_t* self
            = (pipe::filter::encrypt_t*)tolua_tousertype(tolua_S, 1, 0);
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

/* method: new of class  pipe::filter::decrypt_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_decrypt_t_new00
static int tolua_lua_pipe_pipe_filter_decrypt_t_new00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::decrypt_t", 0, &tolua_err)
        || !tolua_isstring(tolua_S, 2, 0, &tolua_err)
        || !tolua_isstring(tolua_S, 3, 0, &tolua_err)
        || !tolua_isstring(tolua_S, 4, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 5, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const char* algorithm = ((const char*)tolua_tostring(tolua_S, 2, 0));
        unsigned const char* key
            = ((unsigned const char*)tolua_tostring(tolua_S, 3, 0));
        unsigned const char* iv
            = ((unsigned const char*)tolua_tostring(tolua_S, 4, 0));
        {
            pipe::filter::decrypt_t* tolua_ret
                = (pipe::filter::decrypt_t*)Mtolua_new(
                    (pipe::filter::decrypt_t)(algorithm, key, iv));
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::decrypt_t");
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

/* method: new_local of class  pipe::filter::decrypt_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_decrypt_t_new00_local
static int tolua_lua_pipe_pipe_filter_decrypt_t_new00_local(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "pipe::filter::decrypt_t", 0, &tolua_err)
        || !tolua_isstring(tolua_S, 2, 0, &tolua_err)
        || !tolua_isstring(tolua_S, 3, 0, &tolua_err)
        || !tolua_isstring(tolua_S, 4, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 5, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const char* algorithm = ((const char*)tolua_tostring(tolua_S, 2, 0));
        unsigned const char* key
            = ((unsigned const char*)tolua_tostring(tolua_S, 3, 0));
        unsigned const char* iv
            = ((unsigned const char*)tolua_tostring(tolua_S, 4, 0));
        {
            pipe::filter::decrypt_t* tolua_ret
                = (pipe::filter::decrypt_t*)Mtolua_new(
                    (pipe::filter::decrypt_t)(algorithm, key, iv));
            tolua_pushusertype(
                tolua_S, (void*)tolua_ret, "pipe::filter::decrypt_t");
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

/* method: delete of class  pipe::filter::decrypt_t */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_filter_decrypt_t_delete00
static int tolua_lua_pipe_pipe_filter_decrypt_t_delete00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "pipe::filter::decrypt_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        pipe::filter::decrypt_t* self
            = (pipe::filter::decrypt_t*)tolua_tousertype(tolua_S, 1, 0);
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

/* function: pipe::pipe */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_pipe01
static int tolua_lua_pipe_pipe_pipe01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (!tolua_iscppstring(tolua_S, 1, 0, &tolua_err)
        || (tolua_isvaluenil(tolua_S, 2, &tolua_err)
            || !tolua_isusertype(
                tolua_S, 2, "pipe::filter::unbase64_t", 0, &tolua_err))
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else {
        const std::string sz
            = ((const std::string)tolua_tocppstring(tolua_S, 1, 0));
        pipe::filter::unbase64_t* filter
            = ((pipe::filter::unbase64_t*)tolua_tousertype(tolua_S, 2, 0));
        {
            std::string tolua_ret = (std::string)pipe::pipe(sz, *filter);
            tolua_pushcppstring(tolua_S, (const char*)tolua_ret);
            tolua_pushcppstring(tolua_S, (const char*)sz);
        }
    }
    return 2;
tolua_lerror:
    return tolua_lua_pipe_pipe_pipe00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: pipe::pipe */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_pipe02
static int tolua_lua_pipe_pipe_pipe02(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (!tolua_iscppstring(tolua_S, 1, 0, &tolua_err)
        || (tolua_isvaluenil(tolua_S, 2, &tolua_err)
            || !tolua_isusertype(
                tolua_S, 2, "pipe::filter::lower_t", 0, &tolua_err))
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else {
        const std::string sz
            = ((const std::string)tolua_tocppstring(tolua_S, 1, 0));
        pipe::filter::lower_t* filter
            = ((pipe::filter::lower_t*)tolua_tousertype(tolua_S, 2, 0));
        {
            std::string tolua_ret = (std::string)pipe::pipe(sz, *filter);
            tolua_pushcppstring(tolua_S, (const char*)tolua_ret);
            tolua_pushcppstring(tolua_S, (const char*)sz);
        }
    }
    return 2;
tolua_lerror:
    return tolua_lua_pipe_pipe_pipe01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: pipe::pipe */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_pipe03
static int tolua_lua_pipe_pipe_pipe03(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (!tolua_iscppstring(tolua_S, 1, 0, &tolua_err)
        || (tolua_isvaluenil(tolua_S, 2, &tolua_err)
            || !tolua_isusertype(
                tolua_S, 2, "pipe::filter::upper_t", 0, &tolua_err))
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else {
        const std::string sz
            = ((const std::string)tolua_tocppstring(tolua_S, 1, 0));
        pipe::filter::upper_t* filter
            = ((pipe::filter::upper_t*)tolua_tousertype(tolua_S, 2, 0));
        {
            std::string tolua_ret = (std::string)pipe::pipe(sz, *filter);
            tolua_pushcppstring(tolua_S, (const char*)tolua_ret);
            tolua_pushcppstring(tolua_S, (const char*)sz);
        }
    }
    return 2;
tolua_lerror:
    return tolua_lua_pipe_pipe_pipe02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: pipe::pipe */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_pipe04
static int tolua_lua_pipe_pipe_pipe04(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (!tolua_iscppstring(tolua_S, 1, 0, &tolua_err)
        || (tolua_isvaluenil(tolua_S, 2, &tolua_err)
            || !tolua_isusertype(
                tolua_S, 2, "pipe::filter::hex_t", 0, &tolua_err))
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else {
        const std::string sz
            = ((const std::string)tolua_tocppstring(tolua_S, 1, 0));
        pipe::filter::hex_t* filter
            = ((pipe::filter::hex_t*)tolua_tousertype(tolua_S, 2, 0));
        {
            std::string tolua_ret = (std::string)pipe::pipe(sz, *filter);
            tolua_pushcppstring(tolua_S, (const char*)tolua_ret);
            tolua_pushcppstring(tolua_S, (const char*)sz);
        }
    }
    return 2;
tolua_lerror:
    return tolua_lua_pipe_pipe_pipe03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: pipe::pipe */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_pipe05
static int tolua_lua_pipe_pipe_pipe05(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (!tolua_iscppstring(tolua_S, 1, 0, &tolua_err)
        || (tolua_isvaluenil(tolua_S, 2, &tolua_err)
            || !tolua_isusertype(
                tolua_S, 2, "pipe::filter::unhex_t", 0, &tolua_err))
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else {
        const std::string sz
            = ((const std::string)tolua_tocppstring(tolua_S, 1, 0));
        pipe::filter::unhex_t* filter
            = ((pipe::filter::unhex_t*)tolua_tousertype(tolua_S, 2, 0));
        {
            std::string tolua_ret = (std::string)pipe::pipe(sz, *filter);
            tolua_pushcppstring(tolua_S, (const char*)tolua_ret);
            tolua_pushcppstring(tolua_S, (const char*)sz);
        }
    }
    return 2;
tolua_lerror:
    return tolua_lua_pipe_pipe_pipe04(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: pipe::pipe */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_pipe06
static int tolua_lua_pipe_pipe_pipe06(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (!tolua_iscppstring(tolua_S, 1, 0, &tolua_err)
        || (tolua_isvaluenil(tolua_S, 2, &tolua_err)
            || !tolua_isusertype(
                tolua_S, 2, "pipe::filter::cut_t", 0, &tolua_err))
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else {
        const std::string sz
            = ((const std::string)tolua_tocppstring(tolua_S, 1, 0));
        pipe::filter::cut_t* filter
            = ((pipe::filter::cut_t*)tolua_tousertype(tolua_S, 2, 0));
        {
            std::string tolua_ret = (std::string)pipe::pipe(sz, *filter);
            tolua_pushcppstring(tolua_S, (const char*)tolua_ret);
            tolua_pushcppstring(tolua_S, (const char*)sz);
        }
    }
    return 2;
tolua_lerror:
    return tolua_lua_pipe_pipe_pipe05(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: pipe::pipe */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_pipe07
static int tolua_lua_pipe_pipe_pipe07(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (!tolua_iscppstring(tolua_S, 1, 0, &tolua_err)
        || (tolua_isvaluenil(tolua_S, 2, &tolua_err)
            || !tolua_isusertype(
                tolua_S, 2, "pipe::filter::zlib_t", 0, &tolua_err))
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else {
        const std::string sz
            = ((const std::string)tolua_tocppstring(tolua_S, 1, 0));
        pipe::filter::zlib_t* filter
            = ((pipe::filter::zlib_t*)tolua_tousertype(tolua_S, 2, 0));
        {
            std::string tolua_ret = (std::string)pipe::pipe(sz, *filter);
            tolua_pushcppstring(tolua_S, (const char*)tolua_ret);
            tolua_pushcppstring(tolua_S, (const char*)sz);
        }
    }
    return 2;
tolua_lerror:
    return tolua_lua_pipe_pipe_pipe06(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: pipe::pipe */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_pipe08
static int tolua_lua_pipe_pipe_pipe08(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (!tolua_iscppstring(tolua_S, 1, 0, &tolua_err)
        || (tolua_isvaluenil(tolua_S, 2, &tolua_err)
            || !tolua_isusertype(
                tolua_S, 2, "pipe::filter::unzlib_t", 0, &tolua_err))
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else {
        const std::string sz
            = ((const std::string)tolua_tocppstring(tolua_S, 1, 0));
        pipe::filter::unzlib_t* filter
            = ((pipe::filter::unzlib_t*)tolua_tousertype(tolua_S, 2, 0));
        {
            std::string tolua_ret = (std::string)pipe::pipe(sz, *filter);
            tolua_pushcppstring(tolua_S, (const char*)tolua_ret);
            tolua_pushcppstring(tolua_S, (const char*)sz);
        }
    }
    return 2;
tolua_lerror:
    return tolua_lua_pipe_pipe_pipe07(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: pipe::pipe */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_pipe09
static int tolua_lua_pipe_pipe_pipe09(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (!tolua_iscppstring(tolua_S, 1, 0, &tolua_err)
        || (tolua_isvaluenil(tolua_S, 2, &tolua_err)
            || !tolua_isusertype(
                tolua_S, 2, "pipe::filter::digest_t", 0, &tolua_err))
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else {
        const std::string sz
            = ((const std::string)tolua_tocppstring(tolua_S, 1, 0));
        pipe::filter::digest_t* filter
            = ((pipe::filter::digest_t*)tolua_tousertype(tolua_S, 2, 0));
        {
            std::string tolua_ret = (std::string)pipe::pipe(sz, *filter);
            tolua_pushcppstring(tolua_S, (const char*)tolua_ret);
            tolua_pushcppstring(tolua_S, (const char*)sz);
        }
    }
    return 2;
tolua_lerror:
    return tolua_lua_pipe_pipe_pipe08(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: pipe::pipe */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_pipe10
static int tolua_lua_pipe_pipe_pipe10(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (!tolua_iscppstring(tolua_S, 1, 0, &tolua_err)
        || (tolua_isvaluenil(tolua_S, 2, &tolua_err)
            || !tolua_isusertype(
                tolua_S, 2, "pipe::filter::encrypt_t", 0, &tolua_err))
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else {
        const std::string sz
            = ((const std::string)tolua_tocppstring(tolua_S, 1, 0));
        pipe::filter::encrypt_t* filter
            = ((pipe::filter::encrypt_t*)tolua_tousertype(tolua_S, 2, 0));
        {
            std::string tolua_ret = (std::string)pipe::pipe(sz, *filter);
            tolua_pushcppstring(tolua_S, (const char*)tolua_ret);
            tolua_pushcppstring(tolua_S, (const char*)sz);
        }
    }
    return 2;
tolua_lerror:
    return tolua_lua_pipe_pipe_pipe09(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: pipe::pipe */
#ifndef TOLUA_DISABLE_tolua_lua_pipe_pipe_pipe11
static int tolua_lua_pipe_pipe_pipe11(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (!tolua_iscppstring(tolua_S, 1, 0, &tolua_err)
        || (tolua_isvaluenil(tolua_S, 2, &tolua_err)
            || !tolua_isusertype(
                tolua_S, 2, "pipe::filter::decrypt_t", 0, &tolua_err))
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else {
        const std::string sz
            = ((const std::string)tolua_tocppstring(tolua_S, 1, 0));
        pipe::filter::decrypt_t* filter
            = ((pipe::filter::decrypt_t*)tolua_tousertype(tolua_S, 2, 0));
        {
            std::string tolua_ret = (std::string)pipe::pipe(sz, *filter);
            tolua_pushcppstring(tolua_S, (const char*)tolua_ret);
            tolua_pushcppstring(tolua_S, (const char*)sz);
        }
    }
    return 2;
tolua_lerror:
    return tolua_lua_pipe_pipe_pipe10(tolua_S);
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
#ifdef __cplusplus
    tolua_cclass(tolua_S, "lower_t", "pipe::filter::lower_t", "",
        tolua_collect_pipe__filter__lower_t);
#else
    tolua_cclass(tolua_S, "lower_t", "pipe::filter::lower_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "lower_t");
    tolua_function(tolua_S, "new", tolua_lua_pipe_pipe_filter_lower_t_new00);
    tolua_function(
        tolua_S, "new_local", tolua_lua_pipe_pipe_filter_lower_t_new00_local);
    tolua_function(
        tolua_S, ".call", tolua_lua_pipe_pipe_filter_lower_t_new00_local);
    tolua_function(
        tolua_S, "delete", tolua_lua_pipe_pipe_filter_lower_t_delete00);
    tolua_endmodule(tolua_S);
#ifdef __cplusplus
    tolua_cclass(tolua_S, "upper_t", "pipe::filter::upper_t", "",
        tolua_collect_pipe__filter__upper_t);
#else
    tolua_cclass(tolua_S, "upper_t", "pipe::filter::upper_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "upper_t");
    tolua_function(tolua_S, "new", tolua_lua_pipe_pipe_filter_upper_t_new00);
    tolua_function(
        tolua_S, "new_local", tolua_lua_pipe_pipe_filter_upper_t_new00_local);
    tolua_function(
        tolua_S, ".call", tolua_lua_pipe_pipe_filter_upper_t_new00_local);
    tolua_function(
        tolua_S, "delete", tolua_lua_pipe_pipe_filter_upper_t_delete00);
    tolua_endmodule(tolua_S);
#ifdef __cplusplus
    tolua_cclass(tolua_S, "hex_t", "pipe::filter::hex_t", "",
        tolua_collect_pipe__filter__hex_t);
#else
    tolua_cclass(tolua_S, "hex_t", "pipe::filter::hex_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "hex_t");
    tolua_function(tolua_S, "new", tolua_lua_pipe_pipe_filter_hex_t_new00);
    tolua_function(
        tolua_S, "new_local", tolua_lua_pipe_pipe_filter_hex_t_new00_local);
    tolua_function(
        tolua_S, ".call", tolua_lua_pipe_pipe_filter_hex_t_new00_local);
    tolua_function(
        tolua_S, "delete", tolua_lua_pipe_pipe_filter_hex_t_delete00);
    tolua_endmodule(tolua_S);
#ifdef __cplusplus
    tolua_cclass(tolua_S, "unhex_t", "pipe::filter::unhex_t", "",
        tolua_collect_pipe__filter__unhex_t);
#else
    tolua_cclass(tolua_S, "unhex_t", "pipe::filter::unhex_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "unhex_t");
    tolua_function(tolua_S, "new", tolua_lua_pipe_pipe_filter_unhex_t_new00);
    tolua_function(
        tolua_S, "new_local", tolua_lua_pipe_pipe_filter_unhex_t_new00_local);
    tolua_function(
        tolua_S, ".call", tolua_lua_pipe_pipe_filter_unhex_t_new00_local);
    tolua_function(
        tolua_S, "delete", tolua_lua_pipe_pipe_filter_unhex_t_delete00);
    tolua_endmodule(tolua_S);
#ifdef __cplusplus
    tolua_cclass(tolua_S, "cut_t", "pipe::filter::cut_t", "",
        tolua_collect_pipe__filter__cut_t);
#else
    tolua_cclass(tolua_S, "cut_t", "pipe::filter::cut_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "cut_t");
    tolua_function(tolua_S, "new", tolua_lua_pipe_pipe_filter_cut_t_new00);
    tolua_function(
        tolua_S, "new_local", tolua_lua_pipe_pipe_filter_cut_t_new00_local);
    tolua_function(
        tolua_S, ".call", tolua_lua_pipe_pipe_filter_cut_t_new00_local);
    tolua_function(
        tolua_S, "delete", tolua_lua_pipe_pipe_filter_cut_t_delete00);
    tolua_endmodule(tolua_S);
#ifdef __cplusplus
    tolua_cclass(tolua_S, "zlib_t", "pipe::filter::zlib_t", "",
        tolua_collect_pipe__filter__zlib_t);
#else
    tolua_cclass(tolua_S, "zlib_t", "pipe::filter::zlib_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "zlib_t");
    tolua_function(tolua_S, "new", tolua_lua_pipe_pipe_filter_zlib_t_new00);
    tolua_function(
        tolua_S, "new_local", tolua_lua_pipe_pipe_filter_zlib_t_new00_local);
    tolua_function(
        tolua_S, ".call", tolua_lua_pipe_pipe_filter_zlib_t_new00_local);
    tolua_function(
        tolua_S, "delete", tolua_lua_pipe_pipe_filter_zlib_t_delete00);
    tolua_endmodule(tolua_S);
#ifdef __cplusplus
    tolua_cclass(tolua_S, "unzlib_t", "pipe::filter::unzlib_t", "",
        tolua_collect_pipe__filter__unzlib_t);
#else
    tolua_cclass(tolua_S, "unzlib_t", "pipe::filter::unzlib_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "unzlib_t");
    tolua_function(tolua_S, "new", tolua_lua_pipe_pipe_filter_unzlib_t_new00);
    tolua_function(
        tolua_S, "new_local", tolua_lua_pipe_pipe_filter_unzlib_t_new00_local);
    tolua_function(
        tolua_S, ".call", tolua_lua_pipe_pipe_filter_unzlib_t_new00_local);
    tolua_function(
        tolua_S, "delete", tolua_lua_pipe_pipe_filter_unzlib_t_delete00);
    tolua_endmodule(tolua_S);
#ifdef __cplusplus
    tolua_cclass(tolua_S, "digest_t", "pipe::filter::digest_t", "",
        tolua_collect_pipe__filter__digest_t);
#else
    tolua_cclass(tolua_S, "digest_t", "pipe::filter::digest_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "digest_t");
    tolua_function(tolua_S, "new", tolua_lua_pipe_pipe_filter_digest_t_new00);
    tolua_function(
        tolua_S, "new_local", tolua_lua_pipe_pipe_filter_digest_t_new00_local);
    tolua_function(
        tolua_S, ".call", tolua_lua_pipe_pipe_filter_digest_t_new00_local);
    tolua_function(
        tolua_S, "delete", tolua_lua_pipe_pipe_filter_digest_t_delete00);
    tolua_endmodule(tolua_S);
#ifdef __cplusplus
    tolua_cclass(tolua_S, "encrypt_t", "pipe::filter::encrypt_t", "",
        tolua_collect_pipe__filter__encrypt_t);
#else
    tolua_cclass(tolua_S, "encrypt_t", "pipe::filter::encrypt_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "encrypt_t");
    tolua_function(tolua_S, "new", tolua_lua_pipe_pipe_filter_encrypt_t_new00);
    tolua_function(
        tolua_S, "new_local", tolua_lua_pipe_pipe_filter_encrypt_t_new00_local);
    tolua_function(
        tolua_S, ".call", tolua_lua_pipe_pipe_filter_encrypt_t_new00_local);
    tolua_function(
        tolua_S, "delete", tolua_lua_pipe_pipe_filter_encrypt_t_delete00);
    tolua_endmodule(tolua_S);
#ifdef __cplusplus
    tolua_cclass(tolua_S, "decrypt_t", "pipe::filter::decrypt_t", "",
        tolua_collect_pipe__filter__decrypt_t);
#else
    tolua_cclass(tolua_S, "decrypt_t", "pipe::filter::decrypt_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "decrypt_t");
    tolua_function(tolua_S, "new", tolua_lua_pipe_pipe_filter_decrypt_t_new00);
    tolua_function(
        tolua_S, "new_local", tolua_lua_pipe_pipe_filter_decrypt_t_new00_local);
    tolua_function(
        tolua_S, ".call", tolua_lua_pipe_pipe_filter_decrypt_t_new00_local);
    tolua_function(
        tolua_S, "delete", tolua_lua_pipe_pipe_filter_decrypt_t_delete00);
    tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    tolua_function(tolua_S, "pipe", tolua_lua_pipe_pipe_pipe00);
    tolua_function(tolua_S, "pipe", tolua_lua_pipe_pipe_pipe01);
    tolua_function(tolua_S, "pipe", tolua_lua_pipe_pipe_pipe02);
    tolua_function(tolua_S, "pipe", tolua_lua_pipe_pipe_pipe03);
    tolua_function(tolua_S, "pipe", tolua_lua_pipe_pipe_pipe04);
    tolua_function(tolua_S, "pipe", tolua_lua_pipe_pipe_pipe05);
    tolua_function(tolua_S, "pipe", tolua_lua_pipe_pipe_pipe06);
    tolua_function(tolua_S, "pipe", tolua_lua_pipe_pipe_pipe07);
    tolua_function(tolua_S, "pipe", tolua_lua_pipe_pipe_pipe08);
    tolua_function(tolua_S, "pipe", tolua_lua_pipe_pipe_pipe09);
    tolua_function(tolua_S, "pipe", tolua_lua_pipe_pipe_pipe10);
    tolua_function(tolua_S, "pipe", tolua_lua_pipe_pipe_pipe11);
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
