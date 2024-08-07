add_library(lua STATIC "")
target_sources(lua PRIVATE
	lua/lapi.c
	lua/lauxlib.c
	lua/lbaselib.c
	lua/lcode.c
	lua/lcorolib.c
	lua/lctype.c
	lua/ldblib.c
	lua/ldebug.c
	lua/ldo.c
	lua/lfunc.c
	lua/lgc.c
	lua/linit.c
	lua/llex.c
	lua/lmathlib.c
	lua/lparser.c
	lua/lstring.c
	lua/lbitlib.c
	lua/ltable.c
	lua/liolib.c
	lua/ldump.c
	lua/ltablib.c
	lua/lvm.c
	lua/lzio.c
	lua/lundump.c
	lua/lobject.c
	lua/lopcodes.c
	lua/lutf8lib.c
	lua/lstate.c
	lua/lfunc.c
	lua/loadlib.c
	lua/lmem.c
	lua/ltm.c
	lua/loslib.c
	lua/lstrlib.c
)

target_include_directories(lua PUBLIC lua)
target_compile_definitions(lua PUBLIC LUA_COMPAT_5_2 LUA_COMPAT_5_1)