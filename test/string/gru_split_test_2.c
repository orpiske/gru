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
#include <stdio.h>
#include <stdlib.h>

#include "collection/gru_list.h"
#include "common/gru_alloc.h"
#include "string/gru_util.h"

int main(int argc, char **argv) {
	gru_status_t status = gru_status_new();
	gru_list_t *list = gru_split(argv[1], argv[2][0], &status);
	uint32_t expected_size = 5;

	if (gru_status_error(&status)) {
		fprintf(stderr, "%s\n", status.message);

		goto err_failure;
	}

	for (uint32_t i = 0; i < argc - 3; i++) {
		const gru_node_t *node = gru_list_get(list, i);
		char *data = (char *) node->data;
		printf("%d = %s\n", i, data);
		if (strcmp(data, argv[i + 3]) != 0) {
			fprintf(stderr, "Expected %s but got %s\n", argv[i + 3], data);
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