/**
 *    Copyright 2017 Otavio Rodolfo Piske <angusyoung@gmail.com>
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>

#include "common/gru_units.h"


int main(int argc, char **argv) {
	const uint64_t bytes = 10048765952;

	if (gru_unit_kb(bytes) != 9813248) {
		fprintf(stderr, "Failed to convert to kilobytes");

		return EXIT_FAILURE;
	}

	if (gru_unit_mb(bytes) != 9583) {
		fprintf(stderr, "Failed to convert to megabytes");

		return EXIT_FAILURE;
	}

	if (gru_unit_gb(bytes) != 9) {
		fprintf(stderr, "Failed to convert to gigabytes");

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}