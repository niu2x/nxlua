add_executable(nxlua "")
target_sources(nxlua PRIVATE
	main.cpp
)
target_link_libraries(nxlua lua-5.1.5)