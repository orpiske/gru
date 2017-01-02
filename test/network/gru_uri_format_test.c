/**
 Copyright 2017 Otavio Rodolfo Piske

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
#include <stdbool.h>
#include <stdlib.h>

#include <common/gru_status.h>
#include <network/gru_uri.h>

bool test1() {
	gru_uri_t uri = {0};
	gru_status_t status = gru_status_new();

	uri.scheme = "test";
	uri.host = "localhost";
	uri.port = 90;
	uri.path = "/root/path";

	char *uri_str = gru_uri_simple_format(&uri, &status);
	if (!uri_str) {
		fprintf(stderr, "%s", status.message);

		return false;
	}

	if (strcmp(uri_str, "test://localhost:90/root/path") != 0) {
		fprintf(stderr, "Invalid URI: %s", uri_str);
		free(uri_str);
		return false;
	}

	free(uri_str);
	return true;
}

bool test2() {
	gru_uri_t uri = {0};
	gru_status_t status = gru_status_new();

	uri.scheme = "test";
	uri.host = "localhost";
	uri.port = 0;
	uri.path = "/root/path";

	char *uri_str = gru_uri_simple_format(&uri, &status);
	if (!uri_str) {
		fprintf(stderr, "%s", status.message);

		return false;
	}

	if (strcmp(uri_str, "test://localhost/root/path") != 0) {
		fprintf(stderr, "Invalid URI: %s", uri_str);
		free(uri_str);
		return false;
	}

	free(uri_str);
	return true;
}

bool test3() {
	gru_uri_t uri = {0};
	gru_status_t status = gru_status_new();

	uri.scheme = "test";
	uri.host = "localhost";
	uri.port = 0;
	uri.path = NULL;

	char *uri_str = gru_uri_simple_format(&uri, &status);
	if (!uri_str) {
		fprintf(stderr, "%s", status.message);

		return false;
	}

	if (strcmp(uri_str, "test://localhost") != 0) {
		fprintf(stderr, "Invalid URI: %s", uri_str);
		free(uri_str);
		return false;
	}

	free(uri_str);
	return true;
}

bool test4() {
	gru_uri_t uri = {0};
	gru_status_t status = gru_status_new();

	uri.scheme = "test";
	uri.host = "localhost";
	uri.port = 99;
	uri.path = NULL;

	char *uri_str = gru_uri_simple_format(&uri, &status);
	if (!uri_str) {
		fprintf(stderr, "%s", status.message);

		return false;
	}

	if (strcmp(uri_str, "test://localhost:99") != 0) {
		fprintf(stderr, "Invalid URI: %s", uri_str);
		free(uri_str);
		return false;
	}

	free(uri_str);
	return true;
}

int main(int argc, char **argv) {
	if (test1()) {
		if (test2()) {
			if (test3()) {
				if (test4()) {
					return EXIT_SUCCESS;
				}
			}
		}
	}

	return EXIT_FAILURE;
}