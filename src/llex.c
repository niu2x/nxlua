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

// void luaX_init (lua_State *L) {
//   int i;
//   for (i=0; i<NUM_RESERVED; i++) {
//     TString *ts = luaS_new(L, luaX_tokens[i]);
//      // reserved words are never collected
//     luaS_fix(ts);
//     lua_assert(strlen(luaX_tokens[i])+1 <= TOKEN_LEN);
//      // reserved word
//     ts->tsv.reserved = cast_byte(i+1);
//   }
// }
