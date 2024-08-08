luas := PreFix.lua \
		class.lua \
		Image.lua \
		mathExt.lua \
		stringExt.lua \
		tableExt.lua \
		path_utils.lua \
		appInit.lua \
		print.lua \
		F.lua \
		welcome.lua \
		dhttp.lua \
		deferred.lua

toluas := image/image.pkg \
			lua_pipe.pkg \
			lua_http.pkg

cpps := $(addprefix src/nxlua/lua_support/pure_lua/, $(luas:.lua=.cpp))
headers := $(addprefix src/nxlua/lua_support/pure_lua/, $(luas:.lua=.h))

all: pure_lua_lib tolua

pure_lua_lib: $(cpps) $(headers) \
				src/nxlua/lua_support/pure_lua_open.cpp
	@echo $^ "=>" $@ 

# src/nxlua/lua_support/pure_lua/%.cpp: src.old/lua/nxlua/%.lua m4/pure_lua.cpp.m4
# 	@m4 -DNAME=$* -DLUA="[$$(cat $<)]" m4/pure_lua.cpp.m4 > $@
# 	clang-format -i $@

src/nxlua/lua_support/pure_lua/%.cpp: src.old/lua/nxlua/%.lua nxlua/pure_lua.cpp.lua
	nxlua/pure_lua.cpp.lua "$<" "$*" > $@
	clang-format -i $@

src/nxlua/lua_support/pure_lua/%.h: src.old/lua/nxlua/%.lua nxlua/pure_lua.h.lua
	nxlua/pure_lua.h.lua "$*" > $@
	clang-format -i $@

src/nxlua/lua_support/pure_lua_open.cpp: $(addprefix src.old/lua/nxlua/, $(luas)) \
								nxlua/pure_lua_open.cpp.lua
	nxlua/pure_lua_open.cpp.lua $(luas) > $@
	clang-format -i $@

tolua: $(addprefix src/nxlua/lua_support/tolua/, $(toluas:.pkg=_binding.cpp)) \
		src/nxlua/lua_support/tolua_libs_open.cpp
	@echo $^ "=>" $@ 

src/nxlua/lua_support/tolua/%_binding.cpp: src/nxlua/lua_support/%.pkg
	mkdir -p $$(dirname $@)
	tolua++5.1 $< > $@
	sed '/tolua_S,"new"/d' -i $@
	sed '/tolua_S,"new_local"/d' -i $@
	sed '/Generated automatically/d' -i $@
	clang-format -i $@

src/nxlua/lua_support/tolua_libs_open.cpp: $(addprefix src/nxlua/lua_support/, $(toluas)) nxlua/tolua_libs_open.cpp.lua
	./nxlua/tolua_libs_open.cpp.lua $(toluas)> $@
	clang-format -i $@

.PHONY: pure_lua_lib tolua
