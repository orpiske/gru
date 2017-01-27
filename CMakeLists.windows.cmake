set(CPP_LIBRARY_DIR "lib")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/target/${CMAKE_INSTALL_BINDIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/target/${CMAKE_INSTALL_LIBDIR})
set (CTEST_BINARY_DIRECTORY ${CMAKE_BINARY_DIR}/target/${CMAKE_INSTALL_LIBDIR})

add_subdirectory(deps/uriparser)
include_directories(${CMAKE_BINARY_DIR}/uriparser/include)

set(URIPARSER_LIB "uriparser")
