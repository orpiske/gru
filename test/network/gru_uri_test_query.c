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
#include <common/gru_keypair.h>
#include <common/gru_variant.h>
#include <log/gru_logger.h>

static bool query_check(gru_uri_t *uri, uint32_t  pos, const char *expected_key, const char *expected_value) {
	const gru_node_t *node = gru_list_get(uri->query, pos);
	const gru_keypair_t *kp1 = node->data;
	if (strcmp(kp1->key, expected_key) != 0) {
		fprintf(
			stderr, "Expected query key '%s' does not match returned one '%s'\n", expected_key, kp1->key);

		return false;
	}

	if (expected_value == NULL) {
		if (kp1->pair->variant.string == NULL) {
			return true;
		}

		return false;
	}

	if (strcmp(kp1->pair->variant.string, expected_value) != 0) {
		fprintf(
			stderr, "Expected query value '%s' does not match returned one '%s'\n", expected_value, kp1->pair->variant.string);

		return false;
	}

	return true;
}

// amqp://localhost:61613/queue amq localhost 61613 /queue
int main(int argc, char **argv) {
	gru_uri_t uri = {0};
	gru_status_t status = gru_status_new();

	gru_logger_set(gru_logger_default_printer);

	if (argc < 3) {
		fprintf(stderr, "Missing arguments\n");
		return EXIT_FAILURE;
	}

	uri = gru_uri_parse(argv[1], &status);

	if (gru_status_error(&status)) {
		fprintf(stderr, "%s", status.message);

		goto err_exit;
	}

	if (strcmp(uri.scheme, argv[2]) != 0) {
		fprintf(stderr,
			"Expected scheme '%s' does not match returned one '%s'\n",
			argv[2],
			uri.scheme);

		goto err_exit;
	}

	if (strcmp(uri.host, argv[3]) != 0) {
		fprintf(
			stderr, "Expected host '%s' does not match returned one '%s'\n", argv[3], uri.host);

		goto err_exit;
	}

	if (uri.port != atoi(argv[4])) {
		fprintf(
			stderr, "Expected port '%s' does not match returned one '%d'\n", argv[2], uri.port);

		goto err_exit;
	}

	if (strcmp(uri.path, argv[5]) != 0) {
		fprintf(
			stderr, "Expected path '%s' does not match returned one '%s'\n", argv[5], uri.path);

		goto err_exit;
	}

	if (!query_check(&uri, 0, argv[6], argv[7])) {
		goto err_exit;
	}

	if (!query_check(&uri, 1, argv[8], argv[9])) {
		goto err_exit;
	}

	if (!query_check(&uri, 2, argv[10], NULL)) {
		goto err_exit;
	}

	gru_uri_cleanup(&uri);
	return EXIT_SUCCESS;

err_exit:
	gru_uri_cleanup(&uri);
	return EXIT_FAILURE;
}
