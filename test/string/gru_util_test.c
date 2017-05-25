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


#include "string/gru_util.h"

int main(int argc, char **argv) {
	char rstr1[] = "abc   ";

	gru_rtrim(rstr1, strlen(rstr1));
	if (strcmp(rstr1,"abc") != 0) {
		fprintf(stderr, "Failed to rtrim string");

		return EXIT_FAILURE;
	}

	char lstr1[] = "   zxd";

	gru_ltrim(lstr1, strlen(lstr1));
	if (strcmp(lstr1,"zxd") != 0) {
		fprintf(stderr, "Failed to ltrim string");

		return EXIT_FAILURE;
	}

	char *str1 = strdup("   123   ");

	str1 = gru_trim(str1, strlen(str1));
	if (strcmp(str1,"123") != 0) {
		fprintf(stderr, "Failed to trim string");

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}