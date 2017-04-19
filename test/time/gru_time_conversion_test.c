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

/**
 * Uses usec value that would cause the conversion to lost precision (ie: usec <= 999)
 */
int test_lost_precision_1() {
	gru_timestamp_t ts = gru_time_read_str("1483228862.529");
	uint64_t expected = 1483228862000; // All the microseconds <= 999 are lost

	uint64_t ret = gru_time_to_milli(&ts);

	if (ret != expected) {
		printf("Returned value %" PRIu64 " does not mach the expected value %" PRIu64
			   "\n",
			ret,
			expected);

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/**
 * Uses usec value that would cause the conversion to lost some precision (ie: usec > 1000)
 */
int test_lost_precision_2() {
	// 1999 = 1 millisecond
	gru_timestamp_t ts = gru_time_read_str("1483228862.1001");
	// All the microseconds thousandth range (ie.: 0 to 999 within eith 1000 units) are
	// lost
	uint64_t expected = 1483228862001;

	uint64_t ret = gru_time_to_milli(&ts);

	if (ret != expected) {
		printf("Returned value %" PRIu64 " does not mach the expected value %" PRIu64
			   "\n",
			ret,
			expected);

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}



int test_lost_precision_3() {
	gru_timestamp_t ts = gru_time_read_str("1492582746.9999998");
	uint64_t expected = 1492582746999;

	uint64_t ret = gru_time_to_milli(&ts);

	if (ret != expected) {
		printf("Returned value %" PRIu64 " does not mach the expected value %" PRIu64
			   "\n",
			ret,
			expected);

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
	if (test_lost_precision_1() == EXIT_SUCCESS) {
		if (test_lost_precision_2() == EXIT_SUCCESS) {
			return test_lost_precision_3();
		}
	}

	return EXIT_FAILURE;
}