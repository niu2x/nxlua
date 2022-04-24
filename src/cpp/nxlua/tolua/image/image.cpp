/*
** Lua binding: image
** Generated automatically by tolua++-1.0.93 on Mon Apr 25 00:39:03 2022.
*/

#ifndef __cplusplus
    #include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_image_open(lua_State* tolua_S);

#include "image/image.h"
using namespace nxlua;

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_image_t(lua_State* tolua_S)
{
    image_t* self = (image_t*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}
#endif

/* function to register type */
static void tolua_reg_types(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "image_t");
}

/* method: new of class  image_t */
#ifndef TOLUA_DISABLE_tolua_image_Image_new00
static int tolua_image_Image_new00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "image_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            image_t* tolua_ret = (image_t*)Mtolua_new((image_t)());
            tolua_pushusertype(tolua_S, (void*)tolua_ret, "image_t");
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

/* method: new_local of class  image_t */
#ifndef TOLUA_DISABLE_tolua_image_Image_new00_local
static int tolua_image_Image_new00_local(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "image_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            image_t* tolua_ret = (image_t*)Mtolua_new((image_t)());
            tolua_pushusertype(tolua_S, (void*)tolua_ret, "image_t");
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

/* method: delete of class  image_t */
#ifndef TOLUA_DISABLE_tolua_image_Image_delete00
static int tolua_image_Image_delete00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "image_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        image_t* self = (image_t*)tolua_tousertype(tolua_S, 1, 0);
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

/* method: load of class  image_t */
#ifndef TOLUA_DISABLE_tolua_image_Image_load00
static int tolua_image_Image_load00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "image_t", 0, &tolua_err)
        || !tolua_isstring(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        image_t* self = (image_t*)tolua_tousertype(tolua_S, 1, 0);
        const char* tolua_var_1 = ((const char*)tolua_tostring(tolua_S, 2, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'load'", NULL);
    #endif
        {
            bool tolua_ret = (bool)self->load(tolua_var_1);
            tolua_pushboolean(tolua_S, (bool)tolua_ret);
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'load'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: save of class  image_t */
#ifndef TOLUA_DISABLE_tolua_image_Image_save00
static int tolua_image_Image_save00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "image_t", 0, &tolua_err)
        || !tolua_isstring(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        image_t* self = (image_t*)tolua_tousertype(tolua_S, 1, 0);
        const char* tolua_var_2 = ((const char*)tolua_tostring(tolua_S, 2, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'save'", NULL);
    #endif
        {
            bool tolua_ret = (bool)self->save(tolua_var_2);
            tolua_pushboolean(tolua_S, (bool)tolua_ret);
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'save'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resample_subimage of class  image_t */
#ifndef TOLUA_DISABLE_tolua_image_Image_resample_subimage00
static int tolua_image_Image_resample_subimage00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "image_t", 0, &tolua_err)
        || !tolua_isusertype(tolua_S, 2, "image_t", 0, &tolua_err)
        || !tolua_isusertype(tolua_S, 3, "image_t", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 4, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 5, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 6, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 7, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 8, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 9, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        image_t* src = ((image_t*)tolua_tousertype(tolua_S, 2, 0));
        image_t* dst = ((image_t*)tolua_tousertype(tolua_S, 3, 0));
        int src_min_x = ((int)tolua_tonumber(tolua_S, 4, 0));
        int src_min_y = ((int)tolua_tonumber(tolua_S, 5, 0));
        int src_max_x = ((int)tolua_tonumber(tolua_S, 6, 0));
        int src_max_y = ((int)tolua_tonumber(tolua_S, 7, 0));
        double angle = ((double)tolua_tonumber(tolua_S, 8, 0));
        {
            image_t::resample_subimage(
                src, dst, src_min_x, src_min_y, src_max_x, src_max_y, angle);
        }
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(
        tolua_S, "#ferror in function 'resample_subimage'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_image_open(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    tolua_reg_types(tolua_S);
    tolua_module(tolua_S, NULL, 0);
    tolua_beginmodule(tolua_S, NULL);
#ifdef __cplusplus
    tolua_cclass(tolua_S, "Image", "image_t", "", tolua_collect_image_t);
#else
    tolua_cclass(tolua_S, "Image", "image_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "Image");
    tolua_function(tolua_S, "new", tolua_image_Image_new00);
    tolua_function(tolua_S, "new_local", tolua_image_Image_new00_local);
    tolua_function(tolua_S, ".call", tolua_image_Image_new00_local);
    tolua_function(tolua_S, "delete", tolua_image_Image_delete00);
    tolua_function(tolua_S, "load", tolua_image_Image_load00);
    tolua_function(tolua_S, "save", tolua_image_Image_save00);
    tolua_function(
        tolua_S, "resample_subimage", tolua_image_Image_resample_subimage00);
    tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    return 1;
}

#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
TOLUA_API int luaopen_image(lua_State* tolua_S)
{
    return tolua_image_open(tolua_S);
};
#endif
