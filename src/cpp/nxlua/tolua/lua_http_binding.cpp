/*
** Lua binding: lua_http
*/

#ifndef __cplusplus
    #include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_lua_http_open(lua_State* tolua_S);

#include "http/send.h"
#include "lua_http.h"
using namespace nxlua;

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_http__response_t(lua_State* tolua_S)
{
    http::response_t* self = (http::response_t*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_http__request_t(lua_State* tolua_S)
{
    http::request_t* self = (http::request_t*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}
#endif

/* function to register type */
static void tolua_reg_types(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "http::response_t");
    tolua_usertype(tolua_S, "http::request_t");
}

/* method: new of class  http::request_t */
#ifndef TOLUA_DISABLE_tolua_lua_http_http_request_t_new00
static int tolua_lua_http_http_request_t_new00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "http::request_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            http::request_t* tolua_ret
                = (http::request_t*)Mtolua_new((http::request_t)());
            tolua_pushusertype(tolua_S, (void*)tolua_ret, "http::request_t");
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

/* method: new_local of class  http::request_t */
#ifndef TOLUA_DISABLE_tolua_lua_http_http_request_t_new00_local
static int tolua_lua_http_http_request_t_new00_local(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "http::request_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            http::request_t* tolua_ret
                = (http::request_t*)Mtolua_new((http::request_t)());
            tolua_pushusertype(tolua_S, (void*)tolua_ret, "http::request_t");
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

/* method: delete of class  http::request_t */
#ifndef TOLUA_DISABLE_tolua_lua_http_http_request_t_delete00
static int tolua_lua_http_http_request_t_delete00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "http::request_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        http::request_t* self
            = (http::request_t*)tolua_tousertype(tolua_S, 1, 0);
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

/* method: set_url of class  http::request_t */
#ifndef TOLUA_DISABLE_tolua_lua_http_http_request_t_set_url00
static int tolua_lua_http_http_request_t_set_url00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "http::request_t", 0, &tolua_err)
        || !tolua_iscppstring(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        http::request_t* self
            = (http::request_t*)tolua_tousertype(tolua_S, 1, 0);
        std::string url = ((std::string)tolua_tocppstring(tolua_S, 2, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'set_url'", NULL);
    #endif
        {
            self->set_url(url);
        }
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'set_url'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set_method of class  http::request_t */
#ifndef TOLUA_DISABLE_tolua_lua_http_http_request_t_set_method00
static int tolua_lua_http_http_request_t_set_method00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "http::request_t", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        http::request_t* self
            = (http::request_t*)tolua_tousertype(tolua_S, 1, 0);
        http::method_t m = ((http::method_t)(int)tolua_tonumber(tolua_S, 2, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(
                tolua_S, "invalid 'self' in function 'set_method'", NULL);
    #endif
        {
            self->set_method(m);
        }
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'set_method'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set_header of class  http::request_t */
#ifndef TOLUA_DISABLE_tolua_lua_http_http_request_t_set_header00
static int tolua_lua_http_http_request_t_set_header00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "http::request_t", 0, &tolua_err)
        || !tolua_iscppstring(tolua_S, 2, 0, &tolua_err)
        || !tolua_iscppstring(tolua_S, 3, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 4, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        http::request_t* self
            = (http::request_t*)tolua_tousertype(tolua_S, 1, 0);
        const std::string key
            = ((const std::string)tolua_tocppstring(tolua_S, 2, 0));
        std::string value = ((std::string)tolua_tocppstring(tolua_S, 3, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(
                tolua_S, "invalid 'self' in function 'set_header'", NULL);
    #endif
        {
            self->set_header(key, value);
            tolua_pushcppstring(tolua_S, (const char*)key);
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'set_header'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  http::response_t */
#ifndef TOLUA_DISABLE_tolua_lua_http_http_response_t_new00
static int tolua_lua_http_http_response_t_new00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "http::response_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            http::response_t* tolua_ret
                = (http::response_t*)Mtolua_new((http::response_t)());
            tolua_pushusertype(tolua_S, (void*)tolua_ret, "http::response_t");
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

/* method: new_local of class  http::response_t */
#ifndef TOLUA_DISABLE_tolua_lua_http_http_response_t_new00_local
static int tolua_lua_http_http_response_t_new00_local(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "http::response_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            http::response_t* tolua_ret
                = (http::response_t*)Mtolua_new((http::response_t)());
            tolua_pushusertype(tolua_S, (void*)tolua_ret, "http::response_t");
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

/* method: delete of class  http::response_t */
#ifndef TOLUA_DISABLE_tolua_lua_http_http_response_t_delete00
static int tolua_lua_http_http_response_t_delete00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "http::response_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        http::response_t* self
            = (http::response_t*)tolua_tousertype(tolua_S, 1, 0);
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

/* method: body of class  http::response_t */
#ifndef TOLUA_DISABLE_tolua_lua_http_http_response_t_body00
static int tolua_lua_http_http_response_t_body00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "const http::response_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const http::response_t* self
            = (const http::response_t*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'body'", NULL);
    #endif
        {
            const std::string tolua_ret = (const std::string)self->body();
            tolua_pushcppstring(tolua_S, (const char*)tolua_ret);
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'body'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: header of class  http::response_t */
#ifndef TOLUA_DISABLE_tolua_lua_http_http_response_t_header00
static int tolua_lua_http_http_response_t_header00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "const http::response_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const http::response_t* self
            = (const http::response_t*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'header'", NULL);
    #endif
        {
            const std::string tolua_ret = (const std::string)self->header();
            tolua_pushcppstring(tolua_S, (const char*)tolua_ret);
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'header'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: http_code of class  http::response_t */
#ifndef TOLUA_DISABLE_tolua_lua_http_http_response_t_http_code00
static int tolua_lua_http_http_response_t_http_code00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "const http::response_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const http::response_t* self
            = (const http::response_t*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(
                tolua_S, "invalid 'self' in function 'http_code'", NULL);
    #endif
        {
            int tolua_ret = (int)self->http_code();
            tolua_pushnumber(tolua_S, (lua_Number)tolua_ret);
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'http_code'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: curl_code of class  http::response_t */
#ifndef TOLUA_DISABLE_tolua_lua_http_http_response_t_curl_code00
static int tolua_lua_http_http_response_t_curl_code00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "const http::response_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const http::response_t* self
            = (const http::response_t*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(
                tolua_S, "invalid 'self' in function 'curl_code'", NULL);
    #endif
        {
            int tolua_ret = (int)self->curl_code();
            tolua_pushnumber(tolua_S, (lua_Number)tolua_ret);
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'curl_code'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: http::lua_send */
#ifndef TOLUA_DISABLE_tolua_lua_http_http_send00
static int tolua_lua_http_http_send00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "http::request_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        http::request_t* request
            = ((http::request_t*)tolua_tousertype(tolua_S, 1, 0));
        lua_Function handler = ((lua_Function)tolua_tovalue(tolua_S, 2, 0));
        {
            http::lua_send(request, handler);
        }
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'send'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_lua_http_open(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    tolua_reg_types(tolua_S);
    tolua_module(tolua_S, NULL, 0);
    tolua_beginmodule(tolua_S, NULL);
    tolua_module(tolua_S, "http", 0);
    tolua_beginmodule(tolua_S, "http");
    tolua_constant(tolua_S, "GET", http::GET);
    tolua_constant(tolua_S, "POST", http::POST);
    tolua_constant(tolua_S, "PUT", http::PUT);
#ifdef __cplusplus
    tolua_cclass(tolua_S, "request_t", "http::request_t", "",
        tolua_collect_http__request_t);
#else
    tolua_cclass(tolua_S, "request_t", "http::request_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "request_t");
    tolua_function(tolua_S, ".call", tolua_lua_http_http_request_t_new00_local);
    tolua_function(tolua_S, "delete", tolua_lua_http_http_request_t_delete00);
    tolua_function(tolua_S, "set_url", tolua_lua_http_http_request_t_set_url00);
    tolua_function(
        tolua_S, "set_method", tolua_lua_http_http_request_t_set_method00);
    tolua_function(
        tolua_S, "set_header", tolua_lua_http_http_request_t_set_header00);
    tolua_endmodule(tolua_S);
#ifdef __cplusplus
    tolua_cclass(tolua_S, "response_t", "http::response_t", "",
        tolua_collect_http__response_t);
#else
    tolua_cclass(tolua_S, "response_t", "http::response_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "response_t");
    tolua_function(
        tolua_S, ".call", tolua_lua_http_http_response_t_new00_local);
    tolua_function(tolua_S, "delete", tolua_lua_http_http_response_t_delete00);
    tolua_function(tolua_S, "body", tolua_lua_http_http_response_t_body00);
    tolua_function(tolua_S, "header", tolua_lua_http_http_response_t_header00);
    tolua_function(
        tolua_S, "http_code", tolua_lua_http_http_response_t_http_code00);
    tolua_function(
        tolua_S, "curl_code", tolua_lua_http_http_response_t_curl_code00);
    tolua_endmodule(tolua_S);
    tolua_function(tolua_S, "send", tolua_lua_http_http_send00);
    tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    return 1;
}

#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
TOLUA_API int luaopen_lua_http(lua_State* tolua_S)
{
    return tolua_lua_http_open(tolua_S);
};
#endif
