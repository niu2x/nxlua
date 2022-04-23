add_executable(nxlua "")

file(GLOB_RECURSE cpp_source "*.cpp")

target_sources(nxlua PRIVATE
	${cpp_source}
)
target_link_libraries(nxlua 
	lua-5.1.5 
	cxxopts 
	linenoise
)