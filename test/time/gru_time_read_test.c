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

#include "time/gru_time_utils.h"

static bool test_read_ex(
	const char *str, const long expected_sec, const long expected_usec) {
	struct timeval t = gru_time_read_str(str);

	if (t.tv_sec != expected_sec) {
		fprintf(stderr,
			"The sec value %ld does not match the expected %ld\n",
			t.tv_sec,
			expected_sec);

		return false;
	}

	if (t.tv_usec != expected_usec) {
		fprintf(stderr,
			"The usec value %li does not match the expected %li\n",
			t.tv_usec,
			expected_usec);

		return false;
	}

	return true;
}

static bool test_read() {
	return test_read_ex("1483228862.529000", 1483228862, 529000);
}

static bool test_write() {
	struct timeval t;

	t.tv_sec = 1562377512;
	t.tv_usec = 671;
	char *tmp = gru_time_write_str(&t);
	if (strcmp(tmp, "1562377512.671") == 0) {
		free(tmp);
		return true;
	}

	fprintf(stderr,
		"Formatted time %s does not match the expected value 1562377512.671\n",
		tmp);
	free(tmp);
	return false;
}

// 1483228862.529
int main(int argc, char **argv) {
	if (test_read()) {
		if (test_write()) {
			return EXIT_SUCCESS;
		}
	}

	return EXIT_FAILURE;
}