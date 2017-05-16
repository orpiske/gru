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

FILE *gru_payload_init_data(gru_payload_t *payload,
	const char *dir,
	const char *name,
	gru_status_t *status) {
	FILE *config_file;

	char *fullpath = gru_path_format(dir, name, status);
	if (fullpath == NULL) {
		return NULL;
	}

	if (gru_status_error(status)) {
		gru_dealloc_string(&fullpath);

		return NULL;
	}

	if (!gru_path_exists(fullpath, status) && gru_status_success(status)) {
		config_file = gru_io_open_file(dir, name, status);
		if (!config_file) {
			goto e_exit;
		}

		// set defaults
		payload->init(payload->data);

		// write configs
		payload->save(config_file, payload->data);

		fflush(config_file);
	} else {
		config_file = gru_io_open_file_read(dir, name, status);
		if (!config_file) {
			goto e_exit;
		}

		payload->read(config_file, payload->data);
	}

	free(fullpath);
	return config_file;

e_exit:
	free(fullpath);
	return NULL;
}