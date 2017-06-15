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
#include <common/gru_status.h>
#include <common/gru_keypair.h>
#include <common/gru_variant.h>

int main(int argc, char **argv) {
	if (argc < 3) {
		fprintf(stderr, "Missing arguments\n");
		return EXIT_FAILURE;
	}

	gru_status_t status = gru_status_new();
	gru_keypair_t *kp = gru_keypair_parse(argv[1], &status);
	if (!kp) {
		fprintf(stderr, "%s\n", status.message);
		return EXIT_FAILURE;
	}

	if (strcmp(kp->key, argv[2]) != 0) {
		fprintf(stderr, "The returned key '%s' does not match the expected key '%s'\n",
				kp->key, argv[2]);

		gru_keypair_destroy(&kp);
		return EXIT_FAILURE;
	}

	if (strcmp(kp->pair->variant.string, argv[3]) != 0) {
		fprintf(stderr, "The returned pair '%s' does not match the expected value '%s'\n",
				kp->pair->variant.string, argv[3]);

		gru_keypair_destroy(&kp);
		return EXIT_FAILURE;
	}

	gru_keypair_destroy(&kp);
	return EXIT_SUCCESS;
}