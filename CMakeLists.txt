cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
project(nxlua VERSION 0.1.0 LANGUAGES CXX C)

add_subdirectory(src/cpp/lua-5.1.5)
add_subdirectory(src/cpp/nxlua)

