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

#ifndef GRU_PAYLOAD_H
#define GRU_PAYLOAD_H

#include <stdio.h>
#include <stdlib.h>

#if !defined(_WIN32) && !defined(_WIN64)
#include <strings.h>
#endif

#include "common/gru_portable.h"
#include "common/gru_status.h"
#include "io/gru_ioutils.h"
#include "io/gru_path.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*gru_payload_data_init_t)(void *);
typedef void (*gru_payload_data_save_t)(FILE *, void *);
typedef void (*gru_payload_data_read_t)(FILE *, void *);

typedef struct gru_payload_t_ {
	gru_payload_data_init_t init;
	gru_payload_data_save_t save;
	gru_payload_data_read_t read;

	void *data;
} gru_payload_t;

gru_export gru_payload_t *gru_payload_init(gru_payload_data_init_t init,
	gru_payload_data_save_t save,
	gru_payload_data_read_t read,
	void *data,
	gru_status_t *status);

gru_export void gru_payload_destroy(gru_payload_t **payload);

gru_export FILE *gru_payload_init_data(gru_payload_t *payload,
	const char *dir,
	const char *name,
	gru_status_t *status);

#ifdef __cplusplus
}
#endif

#endif /* GRU_PAYLOAD_H */
