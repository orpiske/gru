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

int main(int argc, char **argv) {
	gru_timestamp_t ts = gru_time_read_str("1483228862.529");
	uint64_t expected = 1483228862529;

	uint64_t ret = gru_time_to_milli(&ts);

	if (ret != expected) {
		printf("Returned value %" PRIu64 " does not mach the returned value %"
			PRIu64 "\n", ret, expected);
		
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}