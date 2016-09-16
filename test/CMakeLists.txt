PROJECT(gru-tests)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/target/tests/bin)

add_executable(gru_node_test
	collection/gru_node_test.c
)

target_link_libraries(gru_node_test
           gru)

add_test(NAME gru-node
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/bin
    COMMAND gru_node_test)
    
    
add_executable(gru_list_test
	collection/gru_list_test.c
)

target_link_libraries(gru_list_test
           gru)

add_test(NAME gru-list
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/bin
    COMMAND gru_list_test)