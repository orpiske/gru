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
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "time/gru_duration.h"

bool convert_and_check(const char *str, uint64_t expected) {
	gru_duration_t test1 = gru_duration_new();

	if (!gru_duration_parse(&test1, str)) {
		fprintf(stderr, "Unable to parse the given date: %s\n", str);

		return false;
	} else {
		uint64_t seconds = gru_time_elapsed_secs(test1.start, test1.end);
		if (seconds != expected) {
			fprintf(stderr,
				"Invalid number of seconds: %" PRIu64 " / expected %" PRIu64 "\n",
				seconds,
				expected);

			return false;
		} else {
			fprintf(stderr,
				"Returned number of seconds: %" PRIu64 " / expected %" PRIu64 "\n",
				seconds,
				expected);
		}
	}

	return true;
}


int main(int argc, char **argv) {
	if (!convert_and_check("1d", 86400)) {
		return EXIT_FAILURE;
	}

	if (!convert_and_check("1d1h", 90000)) {
		return EXIT_FAILURE;
	}

	if (!convert_and_check("1d1h1m", 90060)) {
		return EXIT_FAILURE;
	}

	if (!convert_and_check("1d1h1m1s", 90061)) {
		return EXIT_FAILURE;
	}

	if (!convert_and_check("2d1m1s", 172861)) {
		return EXIT_FAILURE;
	}

	if (convert_and_check("2dm1s", 172861)) {
		return EXIT_FAILURE;
	}

	if (convert_and_check(NULL, 172861)) {
		return EXIT_FAILURE;
	}

	if (convert_and_check("1", 1)) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}