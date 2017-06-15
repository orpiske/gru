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
#include <math.h>

#include <common/gru_status.h>
#include <common/gru_variant.h>

int main(int argc, char **argv) {
	if (argc < 3) {
		fprintf(stderr, "Missing arguments\n");
		return EXIT_FAILURE;
	}

	gru_variant_t var = gru_variant_parse(argv[1]);

	switch (var.type) {
	case GRU_STRING: {
		if (strcmp(var.variant.string, argv[2]) != 0) {
			fprintf(stderr, "The parsed value '%s' does not match the expected value '%s'\n",
					var.variant.string, argv[2]);

			gru_variant_clean(&var);
			return EXIT_FAILURE;
		}

		break;
	}
	case GRU_INTEGER: {
		if (var.variant.inumber != atoll(argv[2])) {
			fprintf(stderr, "The parsed value '%ld' does not match the expected number value '%s'\n",
					var.variant.inumber, argv[2]);

			gru_variant_clean(&var);
			return EXIT_FAILURE;
		}

		break;
	}
	case GRU_DOUBLE: {
		if (fabs(var.variant.fnumber) != fabs(atof(argv[2]))) {
			fprintf(stderr, "The parsed value '%Lf' does not match the expected float value '%s'\n",
					var.variant.fnumber, argv[2]);

			gru_variant_clean(&var);
			return EXIT_FAILURE;
		}

		break;
	}
	}
	gru_variant_clean(&var);
	return EXIT_SUCCESS;
}