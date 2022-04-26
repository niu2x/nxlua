add_executable(nxlua "")

file(GLOB_RECURSE cpp_source "*.cpp")
file(GLOB_RECURSE c_source "*.c")

target_sources(nxlua PRIVATE
	${cpp_source}
	${c_source}
)
target_link_libraries(nxlua 
	luabitop
	lua-5.1.5 
	linenoise
	cjson
	toluapp_lib
	uv_a
	luv_a
)

target_include_directories(nxlua PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/)
target_include_directories(nxlua PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/stb)
target_include_directories(nxlua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS nxlua DESTINATION bin)
