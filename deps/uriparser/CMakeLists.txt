set (git_cmd "git")
set (git_arg clone --branch uriparser-0.8.4 git://git.code.sf.net/p/uriparser/git uriparser)
execute_process(COMMAND ${git_cmd} ${git_arg}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  RESULT_VARIABLE git_result
  OUTPUT_VARIABLE git_ver)

add_definitions(/DWIN32 /DNDEBUG /D_LIB  /DCRT_SECURE_NO_DEPRECATE /DCRT_NONSTDC_NO_DEPRECATE)

if (WIN32)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/target/bin)
	set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/target/lib)
	set (CTEST_BINARY_DIRECTORY ${CMAKE_BINARY_DIR}/target/lib)
endif (WIN32)


set(RUNTIME_DIR "bin")
set(CPP_INCLUDE_DIR "include")
set(SHARED_DIR "share")

#### GNU Compiler flags

include_directories(uriparser/include uriparser/src)

add_library(
	uriparser SHARED
	uriparser/src/UriCommon.c
	uriparser/src/UriCompare.c
	uriparser/src/UriEscape.c
	uriparser/src/UriFile.c
	uriparser/src/UriIp4.c
	uriparser/src/UriIp4Base.c
	uriparser/src/UriNormalize.c
	uriparser/src/UriNormalizeBase.c
	uriparser/src/UriParse.c
	uriparser/src/UriParseBase.c
	uriparser/src/UriQuery.c
	uriparser/src/UriRecompose.c
	uriparser/src/UriResolve.c
	uriparser/src/UriShorten.c
)

message("Copying uriparser headers")
file(COPY uriparser/include DESTINATION ${CMAKE_BINARY_DIR}/target/)
