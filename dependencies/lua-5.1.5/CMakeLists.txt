add_library(lua-5.1.5 STATIC "")
file(GLOB_RECURSE c_source "*.c")
target_sources(lua-5.1.5 PRIVATE ${c_source})
target_include_directories(lua-5.1.5 PUBLIC ${CMAKE_CURRENT_LIST_DIR})

if ( MSVC )
else()
target_link_libraries(lua-5.1.5 PUBLIC m)
endif ( )


