if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	add_library(ssl STATIC IMPORTED GLOBAL)
	add_library(crypto STATIC IMPORTED GLOBAL)

	SET_TARGET_PROPERTIES(ssl PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/lib64/libssl.a")
	SET_TARGET_PROPERTIES(crypto PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/lib64/libcrypto.a")

	target_include_directories(ssl INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")
	target_include_directories(crypto INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")

endif()