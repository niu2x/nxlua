#include <ctype.h>
#include <locale.h>
#include <string.h>

#include <lua/lua.h>

#include "ldo.h"
#include "llex.h"
#include "lobject.h"
#include "lparser.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"
#include "lzio.h"

#define next(ls) (ls->current = zgetc(ls->z))

#define currIsNewline(ls) (ls->current == '\n' || ls->current == '\r')

/* ORDER RESERVED */
// clang-format off
const char* const luaX_tokens[] = { 
    "and",
    "break", 
    "do", 
    "else", 
    "elseif",
    "end",
    "false",
    "for",
    "function",
    "if",
    "in",
    "local",
    "nil",
    "not",
    "or",
    "repeat",
    "return",
    "then",
    "true",
    "until",
    "while",
    "..",
    "...",
    "==",
    ">=",
    "<=",
    "~=",
    "<number>",
    "<name>",
    "<string>",
    "<eof>",
    NULL
};
// clang-format on

#define save_and_next(ls) (save(ls, ls->current), next(ls))

static void save(LexState* ls, int c)
{
    Mbuffer* b = ls->buff;
    if (b->n + 1 > b->buffsize) {
        size_t newsize;
        if (b->buffsize >= MAX_SIZET / 2)
            luaX_lexerror(ls, "lexical element too long", 0);
        newsize = b->buffsize * 2;
        luaZ_resizebuffer(ls->L, b, newsize);
    }
    b->buffer[b->n++] = cast(char, c);
}

void luaX_init(lua_State* L)
{
    int i;
    for (i = 0; i < NUM_RESERVED; i++) {
        TString* ts = luaS_new(L, luaX_tokens[i]);
        // reserved words are never collected
        luaS_fix(ts);
        lua_assert(strlen(luaX_tokens[i]) + 1 <= TOKEN_LEN);
        // reserved word
        ts->tsv.reserved = cast_byte(i + 1);
    }
}

#define MAXSRC 80

const char* luaX_token2str(LexState* ls, int token)
{
    if (token < FIRST_RESERVED) {
        lua_assert(token == cast(unsigned char, token));
        return (iscntrl(token)) ? luaO_pushfstring(ls->L, "char(%d)", token)
                                : luaO_pushfstring(ls->L, "%c", token);
    } else
        return luaX_tokens[token - FIRST_RESERVED];
}

static const char* txtToken(LexState* ls, int token)
{
    switch (token) {
        case TK_NAME:
        case TK_STRING:
        case TK_NUMBER:
            save(ls, '\0');
            return luaZ_buffer(ls->buff);
        default:
            return luaX_token2str(ls, token);
    }
}

void luaX_lexerror(LexState* ls, const char* msg, int token)
{
    char buff[MAXSRC];
    luaO_chunkid(buff, getstr(ls->source), MAXSRC);
    msg = luaO_pushfstring(ls->L, "%s:%d: %s", buff, ls->linenumber, msg);
    if (token)
        luaO_pushfstring(ls->L, "%s near " LUA_QS, msg, txtToken(ls, token));
    luaD_throw(ls->L, LUA_ERRSYNTAX);
}

void luaX_syntaxerror(LexState* ls, const char* msg)
{
    luaX_lexerror(ls, msg, ls->t.token);
}

// TString *luaX_newstring (LexState *ls, const char *str, size_t l) {
//   lua_State *L = ls->L;
//   TString *ts = luaS_newlstr(L, str, l);
//   TValue *o = luaH_setstr(L, ls->fs->h, ts);  /* entry for `str' */
//   if (ttisnil(o)) {
//     setbvalue(o, 1);  /* make sure `str' will not be collected */
//     luaC_checkGC(L);
//   }
//   return ts;
// }
