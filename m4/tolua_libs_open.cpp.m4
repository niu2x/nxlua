divert(-1)
changecom(@)
changequote([,])

define([TOLUA_BASE],[translit(patsubst(patsubst(TOLUAS, [\.pkg], []), [.*/], []), [ ], [,])])

define(declare_one, 
TOLUA_API int tolua_[]$1[]_open(lua_State* tolua_S);
)
define([declare], [dnl
ifelse($#, 1,[declare_one($1)],[declare_one($1)][declare(shift($@))])dnl
])

define(call_one, 
tolua_[]$1[]_open(L);
)
define([call], [dnl
	ifelse($#, 1,[call_one($1)],[call_one($1)][call(shift($@))])dnl
])


divert(0)dnl
#include <tolua++.h>
declare(TOLUA_BASE)

void tolua_libs_open(lua_State* L) {
call(TOLUA_BASE)dnl
}