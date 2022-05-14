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
		re.lua \
		lupa.lua \
		deferred.lua

toluas := image/image.pkg \
			lua_pipe.pkg

cpps := $(addprefix src/cpp/nxlua/pure_lua/, $(luas:.lua=.cpp))
headers := $(addprefix src/cpp/nxlua/pure_lua/, $(luas:.lua=.h))

all: pure_lua_lib tolua

pure_lua_lib: $(cpps) $(headers) \
				src/cpp/nxlua/pure_lua_open.cpp
	@echo $^ "=>" $@ 

# src/cpp/nxlua/pure_lua/%.cpp: src/lua/nxlua/%.lua m4/pure_lua.cpp.m4
# 	@m4 -DNAME=$* -DLUA="[$$(cat $<)]" m4/pure_lua.cpp.m4 > $@
# 	clang-format -i $@

src/cpp/nxlua/pure_lua/%.cpp: src/lua/nxlua/%.lua nxlua/pure_lua.cpp.lua
	nxlua/pure_lua.cpp.lua "$<" "$*" > $@
	clang-format -i $@

src/cpp/nxlua/pure_lua/%.h: src/lua/nxlua/%.lua m4/pure_lua.h.m4
	@m4 -DNAME=$* m4/pure_lua.h.m4 > $@
	clang-format -i $@

src/cpp/nxlua/pure_lua_open.cpp: $(addprefix src/lua/nxlua/, $(luas)) \
								m4/pure_lua_open.cpp.m4
	@m4 -DLUAS="$(luas)" m4/pure_lua_open.cpp.m4 > $@
	clang-format -i $@

tolua: $(addprefix src/cpp/nxlua/tolua/, $(toluas:.pkg=_binding.cpp)) \
		src/cpp/nxlua/tolua_libs_open.cpp
	@echo $^ "=>" $@ 

src/cpp/nxlua/tolua/%_binding.cpp: src/cpp/nxlua/%.pkg
	mkdir -p $$(dirname $@)
	tolua++5.1 $< > $@
	clang-format -i $@

src/cpp/nxlua/tolua_libs_open.cpp: $(addprefix src/cpp/nxlua/, $(toluas)) m4/tolua_libs_open.cpp.m4
	@m4 -DTOLUAS="$(toluas)" m4/tolua_libs_open.cpp.m4 > $@
	clang-format -i $@

.PHONY: pure_lua_lib tolua
