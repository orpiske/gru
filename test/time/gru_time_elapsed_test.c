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

static bool
	run_calc_secs(gru_timestamp_t start, gru_timestamp_t end, const uint64_t expected) {
	uint64_t elapsed = gru_time_elapsed_secs(start, end);

	if (elapsed != expected) {
		fprintf(stderr,
			"Elapsed time  %" PRIi64 " does not the expected %" PRIi64 "\n",
			elapsed,
			expected);

		return false;
	}

	return true;
}

static bool
	run_calc_milli(gru_timestamp_t start, gru_timestamp_t end, const uint64_t expected) {
	uint64_t elapsed = gru_time_elapsed_milli(start, end);

	if (elapsed != expected) {
		fprintf(stderr,
			"Elapsed time  %" PRIi64 " does not the expected %" PRIi64 "\n",
			elapsed,
			expected);

		return false;
	}

	return true;
}

bool test_sec_same_milli() {
	gru_timestamp_t start = {
		.tv_sec = 1562377512, .tv_usec = 671,
	};

	gru_timestamp_t end = {
		.tv_sec = 1562377522, .tv_usec = 671,
	};

	const uint64_t expected = 10;

	return run_calc_secs(start, end, expected);
}


bool test_sec_diff_milli() {
	gru_timestamp_t start = {
		.tv_sec = 1562377512, .tv_usec = 671,
	};

	gru_timestamp_t end = {
		.tv_sec = 1562377522, .tv_usec = 571,
	};

	const uint64_t expected = 9;

	return run_calc_secs(start, end, expected);
}


bool test_milli_same_sec() {
	gru_timestamp_t start = {
		.tv_sec = 1562377512, .tv_usec = 5000,
	};

	gru_timestamp_t end = {
		.tv_sec = 1562377512, .tv_usec = 104000,
	};

	const uint64_t expected = 99;

	return run_calc_milli(start, end, expected);
}

bool test_milli_diff_sec() {
	gru_timestamp_t start = {
		.tv_sec = 1562377512, .tv_usec = 5000,
	};

	gru_timestamp_t end = {
		.tv_sec = 1562377513,
		.tv_usec = 5001, // The 1 microsecond gets discarded.
	};

	const uint64_t expected = 1000;

	return run_calc_milli(start, end, expected);
}


int main(int argc, char **argv) {

	if (test_sec_same_milli()) {
		if (test_sec_diff_milli()) {
			if (test_milli_same_sec()) {
				if (test_milli_diff_sec()) {
					return EXIT_SUCCESS;
				}
			}
		}
	}

	return EXIT_FAILURE;
}