divert(-1)
changecom(@)
changequote([,])
define(open_one, 
	pure_lua_[]$1[]_open(L);
)
define([open], [dnl
	ifelse($#, 1,[open_one($1)],[open_one($1)][open(shift($@))])dnl
])
define(includex_one, 
#include "pure_lua/$1.h"
)
define([includex], [dnl
ifelse($#, 1, [includex_one($1)], [includex_one($1)][includex(shift($@))])dnl
])
divert(0)dnl
includex(translit(patsubst(LUAS, [\.lua], []), [ ], [,]))
void pure_lua_open(lua_State *L) {
open(translit(patsubst(LUAS, [\.lua], []), [ ], [,]))
}