add_executable(nxlua "")
target_sources(nxlua PRIVATE
	main.cpp
)
target_link_libraries(nxlua lua-5.1.5)
target_include_directories(nxlua PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../lua-5.1.5)