set (git_cmd "git")
set (git_arg clone --branch uriparser-0.8.4 git://git.code.sf.net/p/uriparser/git uriparser)
execute_process(COMMAND ${git_cmd} ${git_arg}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  RESULT_VARIABLE git_result
  OUTPUT_VARIABLE git_ver)

add_definitions(
	/DWIN32
	/DNDEBUG
	/D_LIB
	/DCRT_SECURE_NO_DEPRECATE
	/DCRT_NONSTDC_NO_DEPRECATE)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/target/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/target/lib)
set (CTEST_BINARY_DIRECTORY ${CMAKE_BINARY_DIR}/target/lib)

include_directories(${CMAKE_BINARY_DIR}/uriparser/include ${CMAKE_BINARY_DIR}/uriparser/src)

add_library(
	uriparser SHARED
	${CMAKE_BINARY_DIR}/uriparser/src/UriCommon.c
	${CMAKE_BINARY_DIR}/uriparser/src/UriCompare.c
	${CMAKE_BINARY_DIR}/uriparser/src/UriEscape.c
	${CMAKE_BINARY_DIR}/uriparser/src/UriFile.c
	${CMAKE_BINARY_DIR}/uriparser/src/UriIp4.c
	${CMAKE_BINARY_DIR}/uriparser/src/UriIp4Base.c
	${CMAKE_BINARY_DIR}/uriparser/src/UriNormalize.c
	${CMAKE_BINARY_DIR}/uriparser/src/UriNormalizeBase.c
	${CMAKE_BINARY_DIR}/uriparser/src/UriParse.c
	${CMAKE_BINARY_DIR}/uriparser/src/UriParseBase.c
	${CMAKE_BINARY_DIR}/uriparser/src/UriQuery.c
	${CMAKE_BINARY_DIR}/uriparser/src/UriRecompose.c
	${CMAKE_BINARY_DIR}/uriparser/src/UriResolve.c
	${CMAKE_BINARY_DIR}/uriparser/src/UriShorten.c
)
