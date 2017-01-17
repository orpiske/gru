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

#include "time/gru_time_utils.h"


// 1483228862.529
int main(int argc, char **argv) {
	char *str = "1483228862.529";
	const long expected_sec = 1483228862;
	const long expected_usec = 529;

	struct timeval t = gru_time_read_str(str);

	if (t.tv_sec != expected_sec) {
		fprintf(stderr, "The sec value %ld does not match the expected %ld",
			 t.tv_sec, expected_sec);

		return EXIT_FAILURE;
	}

	if (t.tv_usec != expected_usec) {
		fprintf(stderr, "The usec value %li does not match the expected %li",
			 t.tv_usec, expected_usec);

		return EXIT_FAILURE;
	}

}