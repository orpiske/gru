/*
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

#include "gru_payload.h"
#include "common/gru_alloc.h"

gru_payload_t *gru_payload_init(gru_payload_data_init_t init,
	gru_payload_data_save_t save,
	gru_payload_data_read_t read,
	void *data,
	gru_status_t *status) {
	gru_payload_t *ret = gru_alloc(sizeof(gru_payload_t), status);
	gru_alloc_check(ret, NULL);

	ret->init = init;
	ret->save = save;
	ret->read = read;
	ret->data = data;

	return ret;
}

void gru_payload_destroy(gru_payload_t **payload) {
	free(*payload);
	*payload = NULL;
}

FILE *gru_payload_init_data(gru_payload_t *payload, const char *filename, gru_status_t *status) {
	FILE *config_file;

	if (!gru_path_exists(filename, status) && gru_status_success(status)) {
		config_file = gru_io_open_file_path(filename, status);
		if (!config_file) {
			return NULL;
		}

		// set defaults
		payload->init(payload->data);

		// write configs
		payload->save(config_file, payload->data);

		fflush(config_file);
	} else {
		config_file = gru_io_open_file_read_path(filename, status);
		if (!config_file) {
			return NULL;
		}

		payload->read(config_file, payload->data);
	}

	return config_file;
}


FILE *gru_payload_for_dump(gru_payload_t *payload, const char *filename, gru_status_t *status) {
	FILE *config_file;

	config_file = gru_io_open_file_path(filename, status);
	if (!config_file) {
		return NULL;
	}

	// write configs
	payload->save(config_file, payload->data);

	fflush(config_file);


	return config_file;
}