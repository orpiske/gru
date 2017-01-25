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
#include <network/gru_uri.h>

/**
 * Test code reserved for testing other URI parsing options
 */

// amqp://localhost:61613/queue amq localhost 61613 queue
int test_with_strip(int argc, char **argv) {
	gru_uri_t uri = {0};
	gru_status_t status = gru_status_new();

	if (argc < 3) {
		fprintf(stderr, "Missing arguments\n");
		return EXIT_FAILURE;
	}

	uri = gru_uri_parse_ex(argv[1], GRU_URI_PARSE_STRIP, &status);

	if (gru_status_error(&status)) {
		fprintf(stderr, "%s", status.message);

		goto err_exit;
	}

	if (strcmp(uri.scheme, argv[2]) != 0) {
		fprintf(stderr, "Expected scheme %s does not match returned one %s", argv[2],
			uri.scheme);

		goto err_exit;
	}

	if (strcmp(uri.host, argv[3]) != 0) {
		fprintf(
			stderr, "Expected host %s does not match returned one %s", argv[3], uri.host);

		goto err_exit;
	}

	if (uri.port != atoi(argv[4])) {
		fprintf(
			stderr, "Expected port %s does not match returned one %d", argv[2], uri.port);

		goto err_exit;
	}

	if (strcmp(uri.path, argv[5]) != 0) {
		fprintf(
			stderr, "Expected path %s does not match returned one %s", argv[5], uri.path);

		goto err_exit;
	}

	gru_uri_cleanup(&uri);
	return EXIT_SUCCESS;

err_exit:
	gru_uri_cleanup(&uri);
	return EXIT_FAILURE;
}

int main(int argc, char **argv) { return test_with_strip(argc, argv); }
