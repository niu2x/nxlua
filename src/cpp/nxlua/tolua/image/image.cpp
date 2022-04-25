/*
** Lua binding: image
** Generated automatically by tolua++-1.0.93 on Mon Apr 25 10:50:36 2022.
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

static int tolua_collect_image_t__color_t(lua_State* tolua_S)
{
    image_t::color_t* self = (image_t::color_t*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_image_transform_t(lua_State* tolua_S)
{
    image_transform_t* self
        = (image_transform_t*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}
#endif

/* function to register type */
static void tolua_reg_types(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "image_t");
    tolua_usertype(tolua_S, "image_transform_t");
    tolua_usertype(tolua_S, "image_t::color_t");
}

/* method: translate of class  image_transform_t */
#ifndef TOLUA_DISABLE_tolua_image_image_transform_t_translate00
static int tolua_image_image_transform_t_translate00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "image_transform_t", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 3, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 4, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        double tolua_var_1 = ((double)tolua_tonumber(tolua_S, 2, 0));
        double tolua_var_2 = ((double)tolua_tonumber(tolua_S, 3, 0));
        {
            image_transform_t tolua_ret
                = (image_transform_t)image_transform_t::translate(
                    tolua_var_1, tolua_var_2);
            {
    #ifdef __cplusplus
                void* tolua_obj = Mtolua_new((image_transform_t)(tolua_ret));
                tolua_pushusertype(tolua_S, tolua_obj, "image_transform_t");
                tolua_register_gc(tolua_S, lua_gettop(tolua_S));
    #else
                void* tolua_obj = tolua_copy(
                    tolua_S, (void*)&tolua_ret, sizeof(image_transform_t));
                tolua_pushusertype(tolua_S, tolua_obj, "image_transform_t");
                tolua_register_gc(tolua_S, lua_gettop(tolua_S));
    #endif
            }
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'translate'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scale of class  image_transform_t */
#ifndef TOLUA_DISABLE_tolua_image_image_transform_t_scale00
static int tolua_image_image_transform_t_scale00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "image_transform_t", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 3, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 4, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        double tolua_var_3 = ((double)tolua_tonumber(tolua_S, 2, 0));
        double tolua_var_4 = ((double)tolua_tonumber(tolua_S, 3, 0));
        {
            image_transform_t tolua_ret
                = (image_transform_t)image_transform_t::scale(
                    tolua_var_3, tolua_var_4);
            {
    #ifdef __cplusplus
                void* tolua_obj = Mtolua_new((image_transform_t)(tolua_ret));
                tolua_pushusertype(tolua_S, tolua_obj, "image_transform_t");
                tolua_register_gc(tolua_S, lua_gettop(tolua_S));
    #else
                void* tolua_obj = tolua_copy(
                    tolua_S, (void*)&tolua_ret, sizeof(image_transform_t));
                tolua_pushusertype(tolua_S, tolua_obj, "image_transform_t");
                tolua_register_gc(tolua_S, lua_gettop(tolua_S));
    #endif
            }
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'scale'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rotate of class  image_transform_t */
#ifndef TOLUA_DISABLE_tolua_image_image_transform_t_rotate00
static int tolua_image_image_transform_t_rotate00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "image_transform_t", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        double tolua_var_5 = ((double)tolua_tonumber(tolua_S, 2, 0));
        {
            image_transform_t tolua_ret
                = (image_transform_t)image_transform_t::rotate(tolua_var_5);
            {
    #ifdef __cplusplus
                void* tolua_obj = Mtolua_new((image_transform_t)(tolua_ret));
                tolua_pushusertype(tolua_S, tolua_obj, "image_transform_t");
                tolua_register_gc(tolua_S, lua_gettop(tolua_S));
    #else
                void* tolua_obj = tolua_copy(
                    tolua_S, (void*)&tolua_ret, sizeof(image_transform_t));
                tolua_pushusertype(tolua_S, tolua_obj, "image_transform_t");
                tolua_register_gc(tolua_S, lua_gettop(tolua_S));
    #endif
            }
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'rotate'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  image_transform_t */
#ifndef TOLUA_DISABLE_tolua_image_image_transform_t_new00
static int tolua_image_image_transform_t_new00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "image_transform_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            image_transform_t* tolua_ret
                = (image_transform_t*)Mtolua_new((image_transform_t)());
            tolua_pushusertype(tolua_S, (void*)tolua_ret, "image_transform_t");
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

/* method: new_local of class  image_transform_t */
#ifndef TOLUA_DISABLE_tolua_image_image_transform_t_new00_local
static int tolua_image_image_transform_t_new00_local(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "image_transform_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        {
            image_transform_t* tolua_ret
                = (image_transform_t*)Mtolua_new((image_transform_t)());
            tolua_pushusertype(tolua_S, (void*)tolua_ret, "image_transform_t");
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

/* method: delete of class  image_transform_t */
#ifndef TOLUA_DISABLE_tolua_image_image_transform_t_delete00
static int tolua_image_image_transform_t_delete00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "image_transform_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        image_transform_t* self
            = (image_transform_t*)tolua_tousertype(tolua_S, 1, 0);
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

/* method: mul of class  image_transform_t */
#ifndef TOLUA_DISABLE_tolua_image_image_transform_t_mul00
static int tolua_image_image_transform_t_mul00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "const image_transform_t", 0, &tolua_err)
        || (tolua_isvaluenil(tolua_S, 2, &tolua_err)
            || !tolua_isusertype(
                tolua_S, 2, "const image_transform_t", 0, &tolua_err))
        || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const image_transform_t* self
            = (const image_transform_t*)tolua_tousertype(tolua_S, 1, 0);
        const image_transform_t* right
            = ((const image_transform_t*)tolua_tousertype(tolua_S, 2, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'mul'", NULL);
    #endif
        {
            image_transform_t tolua_ret = (image_transform_t)self->mul(*right);
            {
    #ifdef __cplusplus
                void* tolua_obj = Mtolua_new((image_transform_t)(tolua_ret));
                tolua_pushusertype(tolua_S, tolua_obj, "image_transform_t");
                tolua_register_gc(tolua_S, lua_gettop(tolua_S));
    #else
                void* tolua_obj = tolua_copy(
                    tolua_S, (void*)&tolua_ret, sizeof(image_transform_t));
                tolua_pushusertype(tolua_S, tolua_obj, "image_transform_t");
                tolua_register_gc(tolua_S, lua_gettop(tolua_S));
    #endif
            }
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'mul'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: r of class  color_t */
#ifndef TOLUA_DISABLE_tolua_get_image_t__color_t_r
static int tolua_get_image_t__color_t_r(lua_State* tolua_S)
{
    image_t::color_t* self = (image_t::color_t*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
    if (!self)
        tolua_error(tolua_S, "invalid 'self' in accessing variable 'r'", NULL);
    #endif
    tolua_pushnumber(tolua_S, (lua_Number)self->r);
    return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: r of class  color_t */
#ifndef TOLUA_DISABLE_tolua_set_image_t__color_t_r
static int tolua_set_image_t__color_t_r(lua_State* tolua_S)
{
    image_t::color_t* self = (image_t::color_t*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self)
        tolua_error(tolua_S, "invalid 'self' in accessing variable 'r'", NULL);
    if (!tolua_isnumber(tolua_S, 2, 0, &tolua_err))
        tolua_error(
            tolua_S, "#vinvalid type in variable assignment.", &tolua_err);
    #endif
    self->r = ((int)tolua_tonumber(tolua_S, 2, 0));
    return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: g of class  color_t */
#ifndef TOLUA_DISABLE_tolua_get_image_t__color_t_g
static int tolua_get_image_t__color_t_g(lua_State* tolua_S)
{
    image_t::color_t* self = (image_t::color_t*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
    if (!self)
        tolua_error(tolua_S, "invalid 'self' in accessing variable 'g'", NULL);
    #endif
    tolua_pushnumber(tolua_S, (lua_Number)self->g);
    return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: g of class  color_t */
#ifndef TOLUA_DISABLE_tolua_set_image_t__color_t_g
static int tolua_set_image_t__color_t_g(lua_State* tolua_S)
{
    image_t::color_t* self = (image_t::color_t*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self)
        tolua_error(tolua_S, "invalid 'self' in accessing variable 'g'", NULL);
    if (!tolua_isnumber(tolua_S, 2, 0, &tolua_err))
        tolua_error(
            tolua_S, "#vinvalid type in variable assignment.", &tolua_err);
    #endif
    self->g = ((int)tolua_tonumber(tolua_S, 2, 0));
    return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: b of class  color_t */
#ifndef TOLUA_DISABLE_tolua_get_image_t__color_t_b
static int tolua_get_image_t__color_t_b(lua_State* tolua_S)
{
    image_t::color_t* self = (image_t::color_t*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
    if (!self)
        tolua_error(tolua_S, "invalid 'self' in accessing variable 'b'", NULL);
    #endif
    tolua_pushnumber(tolua_S, (lua_Number)self->b);
    return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: b of class  color_t */
#ifndef TOLUA_DISABLE_tolua_set_image_t__color_t_b
static int tolua_set_image_t__color_t_b(lua_State* tolua_S)
{
    image_t::color_t* self = (image_t::color_t*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self)
        tolua_error(tolua_S, "invalid 'self' in accessing variable 'b'", NULL);
    if (!tolua_isnumber(tolua_S, 2, 0, &tolua_err))
        tolua_error(
            tolua_S, "#vinvalid type in variable assignment.", &tolua_err);
    #endif
    self->b = ((int)tolua_tonumber(tolua_S, 2, 0));
    return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: a of class  color_t */
#ifndef TOLUA_DISABLE_tolua_get_image_t__color_t_a
static int tolua_get_image_t__color_t_a(lua_State* tolua_S)
{
    image_t::color_t* self = (image_t::color_t*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
    if (!self)
        tolua_error(tolua_S, "invalid 'self' in accessing variable 'a'", NULL);
    #endif
    tolua_pushnumber(tolua_S, (lua_Number)self->a);
    return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: a of class  color_t */
#ifndef TOLUA_DISABLE_tolua_set_image_t__color_t_a
static int tolua_set_image_t__color_t_a(lua_State* tolua_S)
{
    image_t::color_t* self = (image_t::color_t*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self)
        tolua_error(tolua_S, "invalid 'self' in accessing variable 'a'", NULL);
    if (!tolua_isnumber(tolua_S, 2, 0, &tolua_err))
        tolua_error(
            tolua_S, "#vinvalid type in variable assignment.", &tolua_err);
    #endif
    self->a = ((int)tolua_tonumber(tolua_S, 2, 0));
    return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  image_t */
#ifndef TOLUA_DISABLE_tolua_image_image_t_new00
static int tolua_image_image_t_new00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_image_image_t_new00_local
static int tolua_image_image_t_new00_local(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_image_image_t_delete00
static int tolua_image_image_t_delete00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_image_image_t_load00
static int tolua_image_image_t_load00(lua_State* tolua_S)
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
        const char* tolua_var_6 = ((const char*)tolua_tostring(tolua_S, 2, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'load'", NULL);
    #endif
        {
            bool tolua_ret = (bool)self->load(tolua_var_6);
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
#ifndef TOLUA_DISABLE_tolua_image_image_t_save00
static int tolua_image_image_t_save00(lua_State* tolua_S)
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
        const char* tolua_var_7 = ((const char*)tolua_tostring(tolua_S, 2, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'save'", NULL);
    #endif
        {
            bool tolua_ret = (bool)self->save(tolua_var_7);
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

/* method: resize of class  image_t */
#ifndef TOLUA_DISABLE_tolua_image_image_t_resize00
static int tolua_image_image_t_resize00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "image_t", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 3, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 4, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        image_t* self = (image_t*)tolua_tousertype(tolua_S, 1, 0);
        int width = ((int)tolua_tonumber(tolua_S, 2, 0));
        int height = ((int)tolua_tonumber(tolua_S, 3, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'resize'", NULL);
    #endif
        {
            self->resize(width, height);
        }
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'resize'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: width of class  image_t */
#ifndef TOLUA_DISABLE_tolua_image_image_t_width00
static int tolua_image_image_t_width00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "const image_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const image_t* self = (const image_t*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'width'", NULL);
    #endif
        {
            int tolua_ret = (int)self->width();
            tolua_pushnumber(tolua_S, (lua_Number)tolua_ret);
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'width'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: height of class  image_t */
#ifndef TOLUA_DISABLE_tolua_image_image_t_height00
static int tolua_image_image_t_height00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "const image_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const image_t* self = (const image_t*)tolua_tousertype(tolua_S, 1, 0);
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'height'", NULL);
    #endif
        {
            int tolua_ret = (int)self->height();
            tolua_pushnumber(tolua_S, (lua_Number)tolua_ret);
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'height'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: fill of class  image_t */
#ifndef TOLUA_DISABLE_tolua_image_image_t_fill00
static int tolua_image_image_t_fill00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "image_t", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 3, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 4, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 5, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 6, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        image_t* self = (image_t*)tolua_tousertype(tolua_S, 1, 0);
        int tolua_var_8 = ((int)tolua_tonumber(tolua_S, 2, 0));
        int tolua_var_9 = ((int)tolua_tonumber(tolua_S, 3, 0));
        int tolua_var_10 = ((int)tolua_tonumber(tolua_S, 4, 0));
        int tolua_var_11 = ((int)tolua_tonumber(tolua_S, 5, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'fill'", NULL);
    #endif
        {
            self->fill(tolua_var_8, tolua_var_9, tolua_var_10, tolua_var_11);
        }
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'fill'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pixel of class  image_t */
#ifndef TOLUA_DISABLE_tolua_image_image_t_pixel00
static int tolua_image_image_t_pixel00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "const image_t", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 3, 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 4, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        const image_t* self = (const image_t*)tolua_tousertype(tolua_S, 1, 0);
        int x = ((int)tolua_tonumber(tolua_S, 2, 0));
        int y = ((int)tolua_tonumber(tolua_S, 3, 0));
    #ifndef TOLUA_RELEASE
        if (!self)
            tolua_error(tolua_S, "invalid 'self' in function 'pixel'", NULL);
    #endif
        {
            image_t::color_t tolua_ret = (image_t::color_t)self->pixel(x, y);
            {
    #ifdef __cplusplus
                void* tolua_obj = Mtolua_new((image_t::color_t)(tolua_ret));
                tolua_pushusertype(tolua_S, tolua_obj, "image_t::color_t");
                tolua_register_gc(tolua_S, lua_gettop(tolua_S));
    #else
                void* tolua_obj = tolua_copy(
                    tolua_S, (void*)&tolua_ret, sizeof(image_t::color_t));
                tolua_pushusertype(tolua_S, tolua_obj, "image_t::color_t");
                tolua_register_gc(tolua_S, lua_gettop(tolua_S));
    #endif
            }
        }
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'pixel'.", &tolua_err);
    return 0;
    #endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resample of class  image_t */
#ifndef TOLUA_DISABLE_tolua_image_image_t_resample00
static int tolua_image_image_t_resample00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "image_t", 0, &tolua_err)
        || !tolua_isusertype(tolua_S, 2, "image_t", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 3, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 4, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 5, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 6, 0, &tolua_err)
        || !tolua_isusertype(tolua_S, 7, "image_t", 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 8, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 9, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 10, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 11, 0, &tolua_err)
        || !tolua_isusertype(
            tolua_S, 12, "const image_transform_t", 0, &tolua_err)
        || !tolua_isnoobj(tolua_S, 13, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        image_t* src = ((image_t*)tolua_tousertype(tolua_S, 2, 0));
        int src_min_x = ((int)tolua_tonumber(tolua_S, 3, 0));
        int src_min_y = ((int)tolua_tonumber(tolua_S, 4, 0));
        int src_width = ((int)tolua_tonumber(tolua_S, 5, 0));
        int src_height = ((int)tolua_tonumber(tolua_S, 6, 0));
        image_t* dst = ((image_t*)tolua_tousertype(tolua_S, 7, 0));
        int dst_min_x = ((int)tolua_tonumber(tolua_S, 8, 0));
        int dst_min_y = ((int)tolua_tonumber(tolua_S, 9, 0));
        int dst_width = ((int)tolua_tonumber(tolua_S, 10, 0));
        int dst_height = ((int)tolua_tonumber(tolua_S, 11, 0));
        const image_transform_t* tolua_var_12
            = ((const image_transform_t*)tolua_tousertype(tolua_S, 12, 0));
        {
            image_t::resample(src, src_min_x, src_min_y, src_width, src_height,
                dst, dst_min_x, dst_min_y, dst_width, dst_height, tolua_var_12);
        }
    }
    return 0;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'resample'.", &tolua_err);
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
    tolua_cclass(tolua_S, "image_transform_t", "image_transform_t", "",
        tolua_collect_image_transform_t);
#else
    tolua_cclass(tolua_S, "image_transform_t", "image_transform_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "image_transform_t");
    tolua_function(
        tolua_S, "translate", tolua_image_image_transform_t_translate00);
    tolua_function(tolua_S, "scale", tolua_image_image_transform_t_scale00);
    tolua_function(tolua_S, "rotate", tolua_image_image_transform_t_rotate00);
    tolua_function(tolua_S, "new", tolua_image_image_transform_t_new00);
    tolua_function(
        tolua_S, "new_local", tolua_image_image_transform_t_new00_local);
    tolua_function(tolua_S, ".call", tolua_image_image_transform_t_new00_local);
    tolua_function(tolua_S, "delete", tolua_image_image_transform_t_delete00);
    tolua_function(tolua_S, "mul", tolua_image_image_transform_t_mul00);
    tolua_endmodule(tolua_S);
#ifdef __cplusplus
    tolua_cclass(tolua_S, "image_t", "image_t", "", tolua_collect_image_t);
#else
    tolua_cclass(tolua_S, "image_t", "image_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "image_t");
#ifdef __cplusplus
    tolua_cclass(tolua_S, "color_t", "image_t::color_t", "",
        tolua_collect_image_t__color_t);
#else
    tolua_cclass(tolua_S, "color_t", "image_t::color_t", "", NULL);
#endif
    tolua_beginmodule(tolua_S, "color_t");
    tolua_variable(tolua_S, "r", tolua_get_image_t__color_t_r,
        tolua_set_image_t__color_t_r);
    tolua_variable(tolua_S, "g", tolua_get_image_t__color_t_g,
        tolua_set_image_t__color_t_g);
    tolua_variable(tolua_S, "b", tolua_get_image_t__color_t_b,
        tolua_set_image_t__color_t_b);
    tolua_variable(tolua_S, "a", tolua_get_image_t__color_t_a,
        tolua_set_image_t__color_t_a);
    tolua_endmodule(tolua_S);
    tolua_function(tolua_S, "new", tolua_image_image_t_new00);
    tolua_function(tolua_S, "new_local", tolua_image_image_t_new00_local);
    tolua_function(tolua_S, ".call", tolua_image_image_t_new00_local);
    tolua_function(tolua_S, "delete", tolua_image_image_t_delete00);
    tolua_function(tolua_S, "load", tolua_image_image_t_load00);
    tolua_function(tolua_S, "save", tolua_image_image_t_save00);
    tolua_function(tolua_S, "resize", tolua_image_image_t_resize00);
    tolua_function(tolua_S, "width", tolua_image_image_t_width00);
    tolua_function(tolua_S, "height", tolua_image_image_t_height00);
    tolua_function(tolua_S, "fill", tolua_image_image_t_fill00);
    tolua_function(tolua_S, "pixel", tolua_image_image_t_pixel00);
    tolua_function(tolua_S, "resample", tolua_image_image_t_resample00);
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
