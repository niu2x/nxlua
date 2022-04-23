cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
project(nxlua VERSION 0.0.0 LANGUAGES CXX C)

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

add_compile_definitions(CMAKE_PROJECT_NAME=${CMAKE_PROJECT_NAME})

add_subdirectory(dependencies/lua-5.1.5)
add_subdirectory(dependencies/cxxopts)
add_subdirectory(dependencies/cpp-linenoise)
add_subdirectory(dependencies/LuaBitOp-1.0.2)
add_subdirectory(dependencies/lua-cjson)
target_compile_definitions(cjson PRIVATE -DENABLE_CJSON_GLOBAL)

add_subdirectory(src/cpp/nxlua)
