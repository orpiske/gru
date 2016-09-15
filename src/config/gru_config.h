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

#ifndef GRU_CONFIG_H
#define GRU_CONFIG_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <pthread.h>
#include <inttypes.h>
#include <assert.h>

#include "common/gru_base.h"
#include "string/gru_util.h"
#include "io/gru_path.h"
#include "io/gru_ioutils.h"

#ifdef __cplusplus
extern "C" {
#endif
    
typedef void(*gru_payload_data_init_t)(void *);
typedef void(*gru_payload_data_save_t)(FILE *, void *);
typedef void *(*gru_payload_data_read_t)(FILE *);

typedef struct gru_payload_t_ {
    gru_payload_data_init_t init;
    gru_payload_data_save_t save;
    gru_payload_data_read_t read;
    
    void *data;
} gru_payload_t;
    
typedef struct gru_config_t_ {
    char *dir;
    char *filename;
    FILE *file;
    
    gru_payload_t *payload;
} gru_config_t;


gru_config_t *gru_config_init(const char *dir, const char *filename, 
                              void *payload, gru_status_t *status);

void gru_config_destroy(gru_config_t **config);

void gru_config_init_payload(gru_config_t *config, gru_payload_t *payload, 
                             gru_status_t *status);

void gru_config_set(char *dest, uint32_t size, const char *fmt, ...);
void gru_config_read(void *dest, FILE *source, const char *mask, const char *name);
void gru_config_read_char(char *dest, FILE *source, const char *name);
void gru_config_read_int(int32_t *dest, FILE *source, const char *name);
void gru_config_read_short(int16_t *dest, FILE *source, const char *name);

void gru_config_write_int(FILE *dest, const char *name, int32_t value);
void gru_config_write_short(FILE *dest, const char *name, int16_t value);
void gru_config_write_string(FILE *dest, const char *name, const char *value);

#ifdef __cplusplus
}
#endif

#endif /* GRU_CONFIG_H */

