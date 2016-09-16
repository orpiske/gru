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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

#include "collection/gru_node.h"
#include "collection/gru_list.h"




int main(int argc, char **argv) {
	gru_status_t status = {0};
	uint32_t list_size = 256;

	gru_list_t *list = gru_list_new(&status);

	if (!list) {
		printf("Unable to create a new list: %s\n", status.message);

		return EXIT_FAILURE;
	}

	for (uint32_t i = 0; i < list_size; i++) {
		uint32_t tmp = i;
		gru_list_append(list, &tmp);
	}

	uint32_t count = gru_list_count(list);
	if (count != 256) {
		printf("Unexpected list size: %i != %i\n", count, list_size);

		return EXIT_FAILURE;
	}

	// gru_node_t *node64 = gru_list_get(list, 64);

	gru_list_destroy(&list);
	if (list != NULL) {
		printf("List incorrectly destroyed\n");

	}


	return EXIT_SUCCESS;
}
