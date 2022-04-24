luas := class.lua

cpps := $(addprefix src/cpp/nxlua/pure_lua/, $(luas:.lua=.cpp))
headers := $(addprefix src/cpp/nxlua/pure_lua/, $(luas:.lua=.h))

pure_lua_lib: $(cpps) $(headers) \
				src/cpp/nxlua/pure_lua_open.cpp
	@echo $^ "=>" $@ 

src/cpp/nxlua/pure_lua/%.cpp: src/lua/nxlua/%.lua m4/pure_lua.cpp.m4
	@m4 -DNAME=$* -DLUA="[$$(cat $<)]" m4/pure_lua.cpp.m4 > $@

src/cpp/nxlua/pure_lua/%.h: src/lua/nxlua/%.lua m4/pure_lua.h.m4
	@m4 -DNAME=$* m4/pure_lua.h.m4 > $@

src/cpp/nxlua/pure_lua_open.cpp: $(addprefix src/lua/nxlua/, $(luas)) \
								m4/pure_lua_open.cpp.m4
	@m4 -DLUAS="$(luas)" m4/pure_lua_open.cpp.m4 > $@

tolua: src/cpp/nxlua/tolua/image/image.cpp
	@echo $^ "=>" $@ 

src/cpp/nxlua/tolua/%.cpp: src/cpp/nxlua/%.pkg
	mkdir -p $$(dirname $@)
	tolua++5.1 $< > $@

.PHONY: pure_lua_lib tolua