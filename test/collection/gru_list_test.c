/**
 Copyright 2016 Otavio Rodolfo Piske

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "collection/gru_list.h"
#include "collection/gru_node.h"

void check_val(const void *nodedata, void *data) {
	bool *exist = (bool *) data;
	uint32_t value = (*(uint32_t *) nodedata);

	if (value == 32) {
		*exist = true;
	}
}

int main(int argc, char **argv) {
	gru_status_t status = {0};
	uint32_t list_size = 256;

	gru_list_t *list = gru_list_new(&status);

	if (!list) {
		printf("Unable to create a new list: %s\n", status.message);

		return EXIT_FAILURE;
	}

#if !defined(_WIN32) && !defined(_WIN64)
	uint32_t tmp[list_size];
#else
	uint32_t tmp[256];
#endif
	for (uint32_t i = 0; i < list_size; i++) {
		tmp[i] = i;
		gru_list_append(list, &tmp[i]);
	}

	uint32_t count = gru_list_count(list);
	if (count != 256) {
		printf("Unexpected list size: %i != %i\n", count, list_size);

		goto e_exit;
	}

	const gru_node_t *node64 = gru_list_get(list, 64);
	if (node64 == NULL) {
		printf("The node does not exist\n");

		goto e_exit;
	}

	uint32_t value = gru_node_get_data(uint32_t, node64);

	if (value != 64) {
		printf(
			"The value of the node does not match the expected: %i != %i\n", value, 64);

		goto e_exit;
	}

	uint32_t new_value = 444;
	gru_node_t *node = gru_list_insert(list, &new_value, 200);
	count = gru_list_count(list);
	if (count != 257) {
		printf("Unexpected list size: %i != %i\n", count, list_size + 1);

		goto e_exit;
	}

	node = gru_list_remove(list, 200);
	gru_node_destroy(&node);

	node = gru_list_remove(list, 200);
	gru_node_destroy(&node);

	node = gru_list_remove(list, 200);
	gru_node_destroy(&node);

	count = gru_list_count(list);
	if (count != 254) {
		printf("Unexpected list size: %i != %i\n", count, 254);

		goto e_exit;
	}

	bool exist = false;
	gru_list_for_each(list, check_val, &exist);
	if (!exist) {
		printf("Value 32 should be present on the list");

		goto e_exit;
	}

	gru_list_destroy(&list);
	if (list != NULL) {
		printf("List incorrectly destroyed\n");

		goto e_exit;
	}

	return EXIT_SUCCESS;

e_exit:
	gru_list_destroy(&list);
	if (list != NULL) {
		printf("List incorrectly destroyed\n");
	}

	return EXIT_FAILURE;
}
