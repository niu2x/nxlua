project(luaxml)
cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

add_library(luaxml STATIC "")
target_sources(luaxml PRIVATE LuaXML_lib.c)
target_link_libraries(luaxml PUBLIC lua-5.1.5)
