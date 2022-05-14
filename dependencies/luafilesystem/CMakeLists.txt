add_library(luafilesystem STATIC "")
target_sources(luafilesystem PRIVATE
	"src/lfs.c"
)

target_include_directories(luafilesystem PUBLIC "${CMAKE_CURRENT_LIST_DIR}/src")
target_link_libraries(luafilesystem lua-5.1.5)