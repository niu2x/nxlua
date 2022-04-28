cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

file(READ ${CMAKE_SOURCE_DIR}/VERSION NXLUA_PROJECT_VERSION)
string(STRIP ${NXLUA_PROJECT_VERSION} NXLUA_PROJECT_VERSION)

project(nxlua VERSION ${NXLUA_PROJECT_VERSION} LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


message(STATUS "build for ${CMAKE_SYSTEM_NAME}")

execute_process (
    COMMAND git rev-parse HEAD
    OUTPUT_VARIABLE NXLUA_GIT_HASH
)
string(STRIP "${NXLUA_GIT_HASH}" NXLUA_GIT_HASH)


add_compile_definitions(NXLUA_PROJECT_NAME=${CMAKE_PROJECT_NAME})
add_compile_definitions(NXLUA_PROJECT_VERSION=${NXLUA_PROJECT_VERSION})
add_compile_definitions(NXLUA_GIT_HASH=${NXLUA_GIT_HASH})

add_subdirectory(dependencies/lua-5.1.5)
add_subdirectory(dependencies/cpp-linenoise)
add_subdirectory(dependencies/LuaBitOp-1.0.2)
add_subdirectory(dependencies/lua-cjson)
target_compile_definitions(cjson PRIVATE -DENABLE_CJSON_GLOBAL)
add_subdirectory(dependencies/libuv EXCLUDE_FROM_ALL)
add_subdirectory(dependencies/luv)
add_subdirectory(dependencies/openssl-3.0.2)
add_subdirectory(dependencies/zlib-1.2.11)

add_subdirectory(src/cpp/nxlua)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(package)
