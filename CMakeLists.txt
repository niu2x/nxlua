cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)
project(nxlua VERSION 0.1.0 LANGUAGES CXX C)

add_library(nxlua "")

file(GLOB_RECURSE c_source "src/*.c")
target_sources(nxlua PRIVATE ${c_source})

target_include_directories(nxlua PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
)

target_include_directories(nxlua PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_compile_features(nxlua PUBLIC cxx_std_17)
set_target_properties(nxlua PROPERTIES
	C_VISIBILITY_PRESET hidden
	CXX_VISIBILITY_PRESET hidden
	VISIBILITY_INLINES_HIDDEN ON
)

include(GenerateExportHeader)
generate_export_header(nxlua
	EXPORT_FILE_NAME include/lua/api.h
	EXPORT_MACRO_NAME LUA_API
	DEPRECATED_MACRO_NAME DEPRECATED_API
	INCLUDE_GUARD_NAME NXLUA_API_H
)

include(CheckSymbolExists)

# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config/build.h.in include/nxlua/build.h)
# warning_as_error_enable(nxlua)

# library alias
add_library(${PROJECT_NAME}::nxlua ALIAS nxlua)

# install & package 
include(GNUInstallDirs)

install(TARGETS nxlua 
	EXPORT nxlua_export 
	INCLUDES DESTINATION
		${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY 
	include/
	${CMAKE_CURRENT_BINARY_DIR}/include/
	TYPE INCLUDE
)

install(EXPORT nxlua_export 
	FILE nxlua-config.cmake 
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake 
	NAMESPACE nxlua::
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
	"nxlua-config-version.cmake"
	COMPATIBILITY SameMajorVersion
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/nxlua-config-version.cmake
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake 
)


# cpack
set(CPACK_GENERATOR ZIP)
include(CPack)