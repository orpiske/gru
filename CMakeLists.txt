project(gru C)
cmake_minimum_required(VERSION 2.8.4)

# Manually sets the version to remain compatible w/ cmake older than 3.0
set(GRU_VERSION_MAJOR 0)
set(GRU_VERSION_MINOR 2)
set(GRU_VERSION_PATCH 0)
set(GRU_VERSION ${GRU_VERSION_MAJOR}.${GRU_VERSION_MINOR}.${GRU_VERSION_PATCH})

include(GNUInstallDirs)
include(CheckLists.cmake)
include(CMakeLists.default.cmake)


set(BUILD_WITH_UNIT_TESTS ON CACHE BOOL "Build unit tests")
set(BUILD_WITH_DOCUMENTATION OFF CACHE BOOL "Build documentation")

if (UNIX)
	message(STATUS "Adding Unix related build rules")
	include(CMakeLists.unix.cmake)
else (UNIX)
	if (WIN32)
		message(STATUS "Adding Windows related build rules")
		include(CMakeLists.windows.cmake)
	endif (WIN32)
endif(UNIX)

link_libraries(${URIPARSER_LIB})
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

if (BUILD_WITH_DOCUMENTATION)
	add_custom_target(documentation ALL
		COMMAND ${CMAKE_COMMAND} -P ../documentation.cmake)
	install(
		DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/target/share/doc 
		DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}-${GRU_VERSION_MAJOR}
	)
endif(BUILD_WITH_DOCUMENTATION)