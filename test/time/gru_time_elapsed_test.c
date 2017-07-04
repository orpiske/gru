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
	run_calc_secs(gru_timestamp_t start, gru_timestamp_t end, const int64_t expected) {
	int64_t elapsed = gru_time_elapsed_secs(start, end);

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
	run_calc_milli(gru_timestamp_t start, gru_timestamp_t end, const int64_t expected) {
	int64_t elapsed = gru_time_elapsed_milli(start, end);

	if (elapsed != expected) {
		fprintf(stderr,
			"Elapsed time  %" PRIi64 " does not match the expected %" PRIi64 "\n",
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

	const int64_t expected = 10;

	return run_calc_secs(start, end, expected);
}


bool test_sec_diff_milli() {
	gru_timestamp_t start = {
		.tv_sec = 1562377512, .tv_usec = 671,
	};

	gru_timestamp_t end = {
		.tv_sec = 1562377522, .tv_usec = 571,
	};

	const int64_t expected = 9;

	return run_calc_secs(start, end, expected);
}

bool test_sec_past() {
	gru_timestamp_t end = {
		.tv_sec = 1562377512, .tv_usec = 671,
	};

	gru_timestamp_t start = {
		.tv_sec = 1562377522, .tv_usec = 671,
	};

	const int64_t expected = -10;

	return run_calc_secs(start, end, expected);
}



bool test_milli_same_sec() {
	gru_timestamp_t start = {
		.tv_sec = 1562377512, .tv_usec = 5000,
	};

	gru_timestamp_t end = {
		.tv_sec = 1562377512, .tv_usec = 104000,
	};

	const int64_t expected = 99;

	return run_calc_milli(start, end, expected);
}

bool test_milli_diff_sec() {
	gru_timestamp_t start = {
		.tv_sec = 1562377512,
		.tv_usec = 5000,
	};

	gru_timestamp_t end = {
		.tv_sec = 1562377513,
		.tv_usec = 5001, // The 1 microsecond gets discarded.
	};

	const int64_t expected = 1000;

	return run_calc_milli(start, end, expected);
}


bool test_milli_diff_sec_past() {
	gru_timestamp_t end = {
		.tv_sec = 1562377512,
		.tv_usec = 5000,
	};

	gru_timestamp_t start = {
		.tv_sec = 1562377513,
		.tv_usec = 5001,
	};

	const int64_t expected = -1001;

	return run_calc_milli(start, end, expected);
}


bool test_add_micro() {
	gru_timestamp_t start = {
		.tv_sec = 1562377512, .tv_usec = 5000,
	};

	// Add 2,5 seconds
	gru_time_add_microseconds(&start, 2500000);

	if (start.tv_sec != 1562377514) {
		fprintf(stderr, "Unexpected time: %"PRIu64"\n", start.tv_sec);
		return false;
	}
	if (start.tv_usec != 505000) {
		fprintf(stderr, "Unexpected time: %"PRIu64"\n", start.tv_usec);
		return false;
	}

	return true;
}


int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Missing test case name\n");

		return EXIT_FAILURE;
	}

	if (strcmp(argv[1], "same-milli") == 0) {
		if (test_sec_same_milli()) {
			return EXIT_SUCCESS;
		}
	} else if (strcmp(argv[1], "diff-milli") == 0) {
		if (test_sec_diff_milli()) {
			return EXIT_SUCCESS;
		}
	} else if (strcmp(argv[1], "sec-past") == 0) {
		if (test_sec_past()) {
			return EXIT_SUCCESS;
		}
	}
	else if (strcmp(argv[1], "same-sec") == 0) {
		if (test_milli_same_sec()) {
			return EXIT_SUCCESS;
		}
	} else if (strcmp(argv[1], "diff-sec") == 0) {
		if (test_milli_diff_sec()) {
			return EXIT_SUCCESS;
		}
	} else if (strcmp(argv[1], "diff-sec-past") == 0) {
		if (test_milli_diff_sec_past()) {
			return EXIT_SUCCESS;
		}
	}
	else if (strcmp(argv[1], "add-micro") == 0) {
		if (test_add_micro()) {
			return EXIT_SUCCESS;
		}
	}

	return EXIT_FAILURE;
}