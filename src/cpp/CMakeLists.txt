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
	uv_a
	luv_a
	crypto
	ssl
	zlibstatic
	luafilesystem
	lpeg
	libcurl
	luaxml
)

# add_compile_definitions(NXLUA_PROJECT_NAME=${CMAKE_PROJECT_NAME})

# add_compile_definitions(NXLUA_PROJECT_VERSION=${NXLUA_PROJECT_VERSION})
# add_compile_definitions(NXLUA_PROJECT_VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR})
# add_compile_definitions(NXLUA_PROJECT_VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR})
# add_compile_definitions(NXLUA_PROJECT_VERSION_PATCH=${CMAKE_PROJECT_VERSION_PATCH})


if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
else()
    target_compile_definitions(nxlua PRIVATE NX_LOG_LEVEL=2)
endif()


check_function_exists(getopt HAS_getopt)

configure_file(nxlua/config.h.in nxlua/config.h)


target_include_directories(nxlua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/toluapp/include)
target_include_directories(nxlua PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/)
target_include_directories(nxlua PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/stb)
target_include_directories(nxlua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(nxlua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/nxlua)
target_include_directories(nxlua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/nxlua/pure_lua)
target_include_directories(nxlua PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS nxlua DESTINATION bin)
