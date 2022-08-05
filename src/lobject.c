#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lua/lua.h>

#include "ldo.h"
#include "lmem.h"
#include "lobject.h"
#include "lstate.h"
#include "lstring.h"
#include "lvm.h"

static void pushstr(lua_State* L, const char* str)
{
    setsvalue2s(L, L->top, luaS_new(L, str));
    incr_top(L);
}

/* this function handles only `%d', `%c', %f, %p, and `%s' formats */
const char* luaO_pushvfstring(lua_State* L, const char* fmt, va_list argp)
{
    int n = 1;
    pushstr(L, "");
    for (;;) {
        const char* e = strchr(fmt, '%');
        if (e == NULL)
            break;
        setsvalue2s(L, L->top, luaS_newlstr(L, fmt, e - fmt));
        incr_top(L);
        switch (*(e + 1)) {
            case 's': {
                const char* s = va_arg(argp, char*);
                if (s == NULL)
                    s = "(null)";
                pushstr(L, s);
                break;
            }
            case 'c': {
                char buff[2];
                buff[0] = cast(char, va_arg(argp, int));
                buff[1] = '\0';
                pushstr(L, buff);
                break;
            }
            case 'd': {
                setnvalue(L->top, cast_num(va_arg(argp, int)));
                incr_top(L);
                break;
            }
            case 'f': {
                setnvalue(L->top, cast_num(va_arg(argp, l_uacNumber)));
                incr_top(L);
                break;
            }
            case 'p': {
                // should be enough space for a `%p'
                char buff[4 * sizeof(void*) + 8];
                sprintf(buff, "%p", va_arg(argp, void*));
                pushstr(L, buff);
                break;
            }
            case '%': {
                pushstr(L, "%");
                break;
            }
            default: {
                char buff[3];
                buff[0] = '%';
                buff[1] = *(e + 1);
                buff[2] = '\0';
                pushstr(L, buff);
                break;
            }
        }
        n += 2;
        fmt = e + 2;
    }
    pushstr(L, fmt);
    luaV_concat(L, n + 1, cast_int(L->top - L->base) - 1);
    L->top -= n;
    return svalue(L->top - 1);
}

const char* luaO_pushfstring(lua_State* L, const char* fmt, ...)
{
    const char* msg;
    va_list argp;
    va_start(argp, fmt);
    msg = luaO_pushvfstring(L, fmt, argp);
    va_end(argp);
    return msg;
}

void luaO_chunkid(char* out, const char* source, size_t bufflen)
{
    if (*source == '=') {
        // remove first char
        strncpy(out, source + 1, bufflen);
        // ensures null termination
        out[bufflen - 1] = '\0';
    } else {
        // out = "source", or "...source"
        if (*source == '@') {
            size_t l;
            // skip the `@'
            source++;
            bufflen -= sizeof(" '...' ");
            l = strlen(source);
            strcpy(out, "");
            if (l > bufflen) {
                source += (l - bufflen); /* get last part of file name */
                strcat(out, "...");
            }
            strcat(out, source);
        } else { /* out = [string "string"] */
            size_t len = strcspn(source, "\n\r"); /* stop at first newline */
            bufflen -= sizeof(" [string \"...\"] ");
            if (len > bufflen)
                len = bufflen;
            strcpy(out, "[string \"");
            if (source[len] != '\0') { /* must truncate? */
                strncat(out, source, len);
                strcat(out, "...");
            } else
                strcat(out, source);
            strcat(out, "\"]");
        }
    }
}
