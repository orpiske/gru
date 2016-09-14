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
#ifndef GRU_PATH_H
#define GRU_PATH_H

#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "common/gru_status.h"

#ifdef __cplusplus
extern "C" {
#endif

#define APPEND_SIZE_REMAP 64

bool gru_path_exists(const char *filename, gru_status_t *status);
bool gru_path_can_read_write(const char *filename, gru_status_t *status);
bool gru_path_rename_if_exists(const char *filename, gru_status_t *status);
char *gru_path_format(const char *dir, const char *name, gru_status_t *status);

#ifdef __cplusplus
}
#endif

#endif /* GRU_PATH_H */

