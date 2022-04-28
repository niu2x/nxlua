cmake_minimum_required(VERSION 2.8)

if(POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW) # faster evaluation of variable references
endif()

project (luv C ASM)

set(LUV_VERSION_MAJOR 1)
set(LUV_VERSION_MINOR 43)
set(LUV_VERSION_PATCH 0)
set(LUV_VERSION ${LUV_VERSION_MAJOR}.${LUV_VERSION_MINOR}.${LUV_VERSION_PATCH})


add_library(luv_a STATIC src/luv.c)
target_link_libraries(luv_a PUBLIC lua-5.1.5 uv_a)
target_include_directories(luv_a PUBLIC ${CMAKE_CURRENT_LIST_DIR}/deps/lua-compat-5.3/c-api)