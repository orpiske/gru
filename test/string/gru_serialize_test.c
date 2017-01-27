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
#include "common/gru_status.h"
#include "string/gru_util.h"

int main(int argc, char **argv) {
	gru_status_t status = gru_status_new();
	gru_list_t *list = gru_list_new(&status);

	gru_list_append(list, "fedora");
	gru_list_append(list, "freebsd");
	gru_list_append(list, "gentoo");
	gru_list_append(list, "debian");
	gru_list_append(list, "ubuntu");
	gru_list_append(list, "red hat");

	char *str = gru_str_serialize(list, ',', &status);
	if (strcmp(str, "fedora,freebsd,gentoo,debian,ubuntu,red hat") != 0) {
		fprintf(
			stderr, "The returned string '%s' does not match the expected one\n", str);

		gru_dealloc_string(&str);
		gru_list_destroy(&list);
		return EXIT_FAILURE;
	}

	gru_dealloc_string(&str);
	gru_list_destroy(&list);
	return EXIT_SUCCESS;
}