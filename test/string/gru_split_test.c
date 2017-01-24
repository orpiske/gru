/*
 * Copyright 2017 Otavio Piske <angusyoung@gmail.com>.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdlib.h>
#include <stdio.h>

#include "string/gru_util.h"
#include "collection/gru_list.h"
#include "common/gru_alloc.h"


int main(int argc, char **argv) {
	gru_status_t status = gru_status_new();
	gru_list_t *list = gru_split("fedora,freebsd,gentoo,debian,ubuntu,red hat", ',',
								 &status);
	uint32_t expected_size = 5;

	if (status.code != GRU_SUCCESS) {
		fprintf(stderr, "%s\n", status.message);

		goto err_failure;
	}

	uint32_t list_size = gru_list_count(list);
	if (list_size != expected_size) {
		fprintf(stderr, "Expected %d but got %d\n", expected_size, list_size);

		goto err_failure;
	}

	const char *expected[] = {
		"fedora",
		"freebsd",
		"gentoo",
		"debian",
		"ubuntu",
		"red hat"
	};

	for (uint32_t i = 0; i < list_size; i++) {
		gru_node_t *node = gru_list_get(list, i);
		char *data = (char *) node->data;
		printf("%d = %s\n", i, data);
		if (strcmp(data, expected[i]) != 0) {
			fprintf("Execpted %s but got %s\n", expected[i], data);
			goto err_failure;
		}
	}


	gru_split_clean(list);
	gru_list_destroy(&list);
	return EXIT_SUCCESS;

	err_failure:
	gru_split_clean(list);
	gru_list_destroy(&list);
	return EXIT_FAILURE;
}