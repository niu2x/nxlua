add_executable(nxlua "")

file(GLOB_RECURSE cpp_source "nxlua/*.cpp")
file(GLOB_RECURSE c_source "nxlua/*.c")

target_sources(nxlua PRIVATE
	${cpp_source}
	${c_source}
)
target_link_libraries(nxlua 
	linenoise
	cjson
	uv_a
	luv_a
	crypto
	ssl
	zlibstatic
	luafilesystem
	libcurl
	luaxml
	lua
)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
else()
    target_compile_definitions(nxlua PRIVATE NX_LOG_LEVEL=2)
endif()

check_function_exists(getopt HAS_getopt)

configure_file(nxlua/config.h.in nxlua/config.h)
target_include_directories(nxlua PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/nxlua)
target_include_directories(nxlua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/nxlua)
target_include_directories(nxlua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/nxlua/lua_support)
target_include_directories(nxlua PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/)
target_include_directories(nxlua PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/stb)

install(TARGETS nxlua DESTINATION bin)
