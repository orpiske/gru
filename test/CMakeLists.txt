project(gru-tests)

if (WIN32)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/target/${CMAKE_INSTALL_LIBDIR})
else (WIN32)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR})
endif (WIN32)

add_executable(
	gru_node_test
	collection/gru_node_test.c
)

target_link_libraries(
	gru_node_test
	gru-${GRU_VERSION_MAJOR}
)

add_test(
	NAME gru-node
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/bin
	COMMAND gru_node_test
)

add_executable(gru_list_test
	collection/gru_list_test.c
)

target_link_libraries(
	gru_list_test
	gru-${GRU_VERSION_MAJOR}
)

add_test(
	NAME gru-list-comprehensive
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_list_test "comprehensive"
)

add_test(
	NAME gru-list-add-remove
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_list_test "addremove"
)


add_executable(
	gru_tree_test
	collection/gru_tree_test.c
)

target_link_libraries(
	gru_tree_test
	gru-${GRU_VERSION_MAJOR}
)

add_test(
	NAME gru-tree
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_tree_test
)

add_executable(
	gru_config_test
	config/gru_config_test.c
)

target_link_libraries(
	gru_config_test
	gru-${GRU_VERSION_MAJOR}
)

add_test(
	NAME gru-config-write
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_config_test "write"
)

add_test(
	NAME gru-config-read
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_config_test "read"
)


add_executable(gru_uri_test
	network/gru_uri_test.c
)

target_link_libraries(
	gru_uri_test
	gru-${GRU_VERSION_MAJOR}
)

add_test(
	NAME gru-uri-test-1
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_uri_test amqp://localhost:61613/queue amqp localhost 61613 /queue
)

add_test(
	NAME gru-uri-test-2
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_uri_test http://localhost/ http localhost "" /
)

add_test(
	NAME gru-uri-test-3
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_uri_test http://localhost/path http localhost "" /path
)


add_test(
	NAME gru-uri-test-4
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_uri_test http://localhost/path/subpath http localhost "" /path/subpath
)

add_test(
	NAME gru-uri-test-5
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_uri_test https://10.0.0.1/path/subpath https 10.0.0.1 "" /path/subpath
)

add_test(
	NAME gru-uri-test-6
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_uri_test https://10.0.0.1 https 10.0.0.1 "" ""
)


add_executable(gru_uri_format_test
	network/gru_uri_format_test.c
)

target_link_libraries(
	gru_uri_format_test
	gru-${GRU_VERSION_MAJOR}
)

add_test(
	NAME gru-uri-format-test
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_uri_format_test
)


add_executable(gru_uri_test_opt
	network/gru_uri_test_opt.c
)

target_link_libraries(
	gru_uri_test_opt
	gru-${GRU_VERSION_MAJOR}
)

add_test(
	NAME gru-uri-test-opt
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_uri_test_opt amqp://localhost:61613/queue amqp localhost 61613 queue
)


add_executable(gru_time_read_test
	time/gru_time_read_test.c
)

target_link_libraries(
	gru_time_read_test
	gru-${GRU_VERSION_MAJOR}
)

add_test(
	NAME gru-time-read-test
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_time_read_test
)


add_executable(gru_time_conversion_test
	time/gru_time_conversion_test.c
)

target_link_libraries(
	gru_time_conversion_test
	gru-${GRU_VERSION_MAJOR}
)

add_test(
	NAME gru-time-conversion-test
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_time_conversion_test
)



add_executable(gru_time_elapsed_test
	time/gru_time_elapsed_test.c
)

target_link_libraries(
	gru_time_elapsed_test
	gru-${GRU_VERSION_MAJOR}
)

add_test(
	NAME gru-time-elapsed-test
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_time_elapsed_test
)

add_executable(
	gru_split_test
	string/gru_split_test.c
)

target_link_libraries(
	gru_split_test
	gru-${GRU_VERSION_MAJOR}
)

add_test(
	NAME gru-split
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_split_test
)


add_executable(
	gru_split_test_2
	string/gru_split_test_2.c
)

target_link_libraries(
	gru_split_test_2
	gru-${GRU_VERSION_MAJOR}
)

add_test(
	NAME gru-split-2
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_split_test_2 "net,java" "," "net" "java"
)

add_executable(
	gru_serialize_test
	string/gru_serialize_test.c
)

target_link_libraries(
	gru_serialize_test
	gru-${GRU_VERSION_MAJOR}
)

add_test(
	NAME gru-serialize
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/${CMAKE_INSTALL_BINDIR}
	COMMAND gru_serialize_test
)