# uninstall
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/dist/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/dist/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/dist/cmake_uninstall.cmake)

if (CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_C_FLAGS "-Wall -Wshadow -Wconversion -Wno-sign-conversion -fstrict-aliasing -fstack-protector-all -std=c99 ${CMAKE_USER_C_FLAGS}" CACHE STRING
		"Flags used by the compiler during all build types." FORCE
	)

	set(CMAKE_C_FLAGS_DEBUG "-fdiagnostics-color=auto -g -fstack-protector-all ${CMAKE_USER_C_FLAGS}"  CACHE STRING
		"Flags used by the compiler during debug build." FORCE
	)

	set(CMAKE_C_FLAGS_RELEASE "-O2 -fomit-frame-pointer -D_FORTIFY_SOURCE=1 -fstack-protector-all ${CMAKE_USER_C_FLAGS}" CACHE STRING
		"Flags used by the compiler during release build." FORCE
	)
endif (CMAKE_COMPILER_IS_GNUCXX)
