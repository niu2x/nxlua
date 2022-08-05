#include <string.h>

#include <lua/lua.h>

#include "lmem.h"
#include "lobject.h"
#include "lstate.h"
#include "lstring.h"

static TString* TString_alloc(lua_State* L, size_t l)
{
    size_t size = sizeof(TString) + (l + 1) * sizeof(char);
    return cast(TString*, luaM_malloc(L, size));
}

void luaS_resize(lua_State* L, int newsize)
{
    GCObject** newhash;
    stringtable* tb;
    int i;
    // cannot resize during GC traverse
    if (G(L)->gcstate == GCSsweepstring)
        return;
    newhash = luaM_newvector(L, newsize, GCObject*);
    tb = &G(L)->strt;
    for (i = 0; i < newsize; i++)
        newhash[i] = NULL;
    /* rehash */
    for (i = 0; i < tb->size; i++) {
        GCObject* p = tb->hash[i];
        while (p) { /* for each node in the list */
            GCObject* next = p->gch.next; /* save next */
            unsigned int h = gco2ts(p)->hash;
            int h1 = lmod(h, newsize); /* new position */
            lua_assert(cast_int(h % newsize) == lmod(h, newsize));
            p->gch.next = newhash[h1]; /* chain it */
            newhash[h1] = p;
            p = next;
        }
    }
    luaM_freearray(L, tb->hash, tb->size, TString*);
    tb->size = newsize;
    tb->hash = newhash;
}

static TString* newlstr(lua_State* L, const char* str, size_t l, unsigned int h)
{
    TString* ts;
    stringtable* tb;
    if (l + 1 > (MAX_SIZET - sizeof(TString)) / sizeof(char))
        luaM_toobig(L);
    ts = TString_alloc(L, l);
    ts->tsv.len = l;
    ts->tsv.hash = h;
    ts->tsv.marked = luaC_white(G(L));
    ts->tsv.tt = LUA_TSTRING;
    ts->tsv.reserved = 0;
    memcpy(ts + 1, str, l * sizeof(char));
    ((char*)(ts + 1))[l] = '\0'; /* ending 0 */
    tb = &G(L)->strt;
    h = lmod(h, tb->size);
    ts->tsv.next = tb->hash[h]; /* chain new entry */
    tb->hash[h] = obj2gco(ts);
    tb->nuse++;
    if (tb->nuse > cast(lu_int32, tb->size) && tb->size <= MAX_INT / 2)
        luaS_resize(L, tb->size * 2); /* too crowded */
    return ts;
}

TString* luaS_newlstr(lua_State* L, const char* str, size_t l)
{
    GCObject* o;
    // seed
    unsigned int h = cast(unsigned int, l);
    // if string is too long, don't hash all its chars
    size_t step = (l >> 5) + 1;
    size_t l1;
    for (l1 = l; l1 >= step; l1 -= step) /* compute hash */
        h = h ^ ((h << 5) + (h >> 2) + cast(unsigned char, str[l1 - 1]));
    for (o = G(L)->strt.hash[lmod(h, G(L)->strt.size)]; o != NULL;
         o = o->gch.next) {
        TString* ts = rawgco2ts(o);
        if (ts->tsv.len == l && (memcmp(str, getstr(ts), l) == 0)) {
            /* string may be dead */
            if (isdead(G(L), o))
                changewhite(o);
            return ts;
        }
    }
    // not found
    return newlstr(L, str, l, h);
}