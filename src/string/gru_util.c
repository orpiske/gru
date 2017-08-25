/*
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
#include <stdint.h>

#include "collection/gru_list.h"
#include "common/gru_alloc.h"
#include "gru_util.h"

char *gru_rtrim(char *input, size_t size) {
	size_t i = size - 1;

	assert(input != NULL);

	while ((isspace(input[i]) || input[i] == 0) && i > 0) {
		input[i] = 0;
		i--;
	}

	if (i == 0) {
		if (isspace(input[0])) {
			input[0] = 0;
		}
	}

	return input;
}

char *gru_ltrim(char *input, size_t size) {
	size_t i = 0;
	assert(input != NULL);

	while ((i < (size - 1)) && isspace(input[i])) {
		i++;
	}

	if (i > 0) {
		memmove(input, input + i, size - i);
		memset(input + (size - i), 0, i);
	}

	return input;
}

char *gru_trim(char *input, size_t size) {
	size_t tmp_size = 0;

	char *tmp_string = gru_rtrim(input, size);
	tmp_size = strnlen(tmp_string, size);

	return gru_ltrim(tmp_string, tmp_size);
}

const char *gru_get_name_from_url(const char *url, size_t size) {
	size_t i = 0;

	for (i = size; i > 0; i--) {
		if (url[i] == '/') {
			return (char *) &url[i + 1];
		}
	}

	return NULL;
}

gru_list_t *gru_split(const char *str, char sep, gru_status_t *status) {
	gru_list_t *ret = gru_list_new(status);
	gru_alloc_check(ret, NULL);

	size_t len = strlen(str);
	size_t last = 0;
	for (size_t i = 0; i <= len; i++) {
		if (str[i] == sep || str[i] == 0) {
			char *tok = strndup(str + last, i - last);
			gru_list_append(ret, tok);
			last = i + 1;

			if (str[i] == 0) {
				break;
			}
		}
	}

	return ret;
}

void gru_split_clean(gru_list_t *list) {
	gru_list_clean(list, gru_dealloc);
}

char *gru_str_serialize(gru_list_t *list, char sep, gru_status_t *status) {
	uint32_t lsize = gru_list_count(list);
	size_t strsize = 0;

	for (uint32_t i = 0; i < lsize; i++) {
		const gru_node_t *node = gru_list_get(list, i);
		const char *str = (const char *) node->data;
		strsize += strlen(str) + 1;
	}

	char *ret = gru_alloc(strsize + 1, status);
	if (!ret) {
		return NULL;
	}

	char sep2[2] = {0};
	sep2[0] = sep;

	for (uint32_t i = 0; i < lsize; i++) {
		const gru_node_t *node = gru_list_get(list, i);
		const char *str = (const char *) node->data;

		strlcat(ret, str, strsize);
		strlcat(ret, sep2, strsize);
	}

	return ret;
}