project(gru)
cmake_minimum_required(VERSION 2.6)

# Manually sets the version to remain compatible w/ cmake older than 3.0
set(GRU_VERSION 0.1.0)
set(GRU_VERSION_MAJOR 0)
set(GRU_VERSION_MINOR 1)
set(GRU_VERSION_PATCH 0)

include(CheckLists.cmake)
include(CMakeLists.default.cmake)

set(BUILD_WITH_UNIT_TESTS ON CACHE BOOL "Build unit tests")

if (UNIX)
	message(STATUS "Adding Unix related build rules")
	include(CMakeLists.unix.cmake)
else (UNIX)
	if (WIN32)
		message(STATUS "Adding Windows related build rules")
		include(CMakeLists.windows.cmake)
	endif (WIN32)
endif(UNIX)

if (WIN32)
	add_subdirectory(deps/uriparser)
	include_directories(${CMAKE_BINARY_DIR}/uriparser/include)
endif (WIN32)

link_libraries(uriparser)
include_directories(src)

add_subdirectory(src/ objs)

if (BUILD_WITH_UNIT_TESTS)
	enable_testing()

	include_directories(test)
	add_subdirectory(test)
endif (BUILD_WITH_UNIT_TESTS)

add_custom_target(format
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/util/format.sh
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
