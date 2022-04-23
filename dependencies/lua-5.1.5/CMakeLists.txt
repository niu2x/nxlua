add_library(lua-5.1.5 STATIC "")
file(GLOB_RECURSE c_source "*.c")
target_sources(lua-5.1.5 PRIVATE ${c_source})