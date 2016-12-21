project(gru-tests)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/target/lib)

add_executable(
	gru_node_test
	collection/gru_node_test.c
)

target_link_libraries(
	gru_node_test
	gru)

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
	gru
)

add_test(
	NAME gru-list
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/bin
	COMMAND gru_list_test
)

add_executable(
	gru_tree_test
	collection/gru_tree_test.c
)

target_link_libraries(
	gru_tree_test
	gru
)

add_test(
	NAME gru-tree
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/bin
	COMMAND gru_tree_test
)

add_executable(
	gru_config_test
	config/gru_config_test.c
)

target_link_libraries(
	gru_config_test
	gru)

add_test(
	NAME gru-config-write
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/bin
	COMMAND gru_config_test "write"
)

add_test(
	NAME gru-config-read
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/bin
	COMMAND gru_config_test "read"
)
