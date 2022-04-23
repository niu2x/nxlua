add_executable(nxlua "")

file(GLOB_RECURSE cpp_source "*.cpp")
file(GLOB_RECURSE c_source "*.c")

target_sources(nxlua PRIVATE
	${cpp_source}
	${c_source}
)
target_link_libraries(nxlua 
	cxxopts 
	luabitop
	lua-5.1.5 
	linenoise
	cjson
)