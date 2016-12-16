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
#include "gru_util.h"


char *gru_rtrim(char *input, size_t size) {
	size_t i = size;

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

	while (isspace(input[i])) {
		i++;
	}

	if (i > 0) {
		memcpy(input, input + i, size - i);
		memset(input + (size - i), 0, i);
	}

	return input;
}


char *gru_trim(char *input, size_t size) {
	size_t tmp_size = 0;
	char *tmp_string = NULL;

	tmp_string = gru_rtrim(input, size);
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
