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
#include "gru_status.h"

gru_export inline gru_status_t gru_status_new() {
	gru_status_t ret = {
		.code = GRU_SUCCESS, .message = NULL,
	};

	return ret;
}

void gru_status_set(gru_status_t *status,
	gru_status_code_t code,
	const char *message,
	...) {
	assert(status);

	if (status->message != NULL) {
		gru_status_reset(status);
	}

	if (message != NULL) {
		va_list ap;

		va_start(ap, message);
		if (vasprintf(&status->message, message, ap) == -1) {
			fprintf(stderr, "Unable to allocate memory for the message: %s", message);
		}
		va_end(ap);
	}

	status->code = code;
}

void gru_status_reset(gru_status_t *status) {
	free(status->message);
	status->message = NULL;
	status->code = GRU_SUCCESS;
}

void gru_status_set_success(gru_status_t *status) {
	gru_status_set(status, GRU_SUCCESS, NULL);
}

void gru_status_strerror(gru_status_t *status, gru_status_code_t code, int errnum) {
	gru_status_reset(status);

#if defined(_GNU_SOURCE)

	char *message = (char *) calloc(1, GRU_MAX_ERROR_MESSAGE);
	if (!message) {
		fprintf(stderr, "Not enough memory to allocate for the error message");

		return;
	}

	char *tmpmsg = strerror_r(errnum, message, GRU_MAX_ERROR_MESSAGE);
	gru_status_set(status, code, tmpmsg);

	free(message);
#else
	char buff[GRU_MAX_ERROR_MESSAGE] = {0};

	strerror_r(errnum, buff, GRU_MAX_ERROR_MESSAGE);
	gru_status_set(status, code, buff);
#endif
}

inline bool gru_status_error(const gru_status_t *status) {
	return status->code == GRU_FAILURE;
}

inline bool gru_status_success(const gru_status_t *status) {
	return status->code == GRU_SUCCESS;
}