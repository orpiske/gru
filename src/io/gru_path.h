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

#ifndef FILE_SEPARATOR
#define FILE_SEPARATOR "/"
#endif
    
typedef bool(*gru_path_cond_t)(const char *, gru_status_t *status);

/**
 * Checks whether a given file exists
 * @param filename the filename
 * @param status status structure containing error code/description in case of 
 * failure
 * @return
 */
bool gru_path_exists(const char *filename, gru_status_t *status);

/**
 * Checks whether can read/write a given file
 * @param filename the filename
 * @param status status structure containing error code/description in case of 
 * failure
 * @return
 */
bool gru_path_can_read_write(const char *filename, gru_status_t *status);


/**
 * Renames a file based on a condition
 * @param filename the filename
 * @param cond condition that must be fulfilled for the rename to occur
 * @param status status structure containing error code/description in case of 
 * failure
 * @return true if successful or false otherwise
 */
bool gru_path_rename_cond(const char *filename, gru_path_cond_t cond, 
                          gru_status_t *status);


/**
 * Renames a file
 * @param filename the filename
 * @param status status structure containing error code/description in case of 
 * failure
 * @return true if successful or false otherwise
 */
bool gru_path_rename(const char *filename, gru_status_t *status);


/**
 * Formats a path
 * @param dir directory of the file
 * @param name name of the file
 * @param status status structure containing error code/description in case of 
 * failure
 * @return the formatted path
 */
char *gru_path_format(const char *dir, const char *name, gru_status_t *status);

/**
 * Create a directory
 * @param path directory path
 * @param status status structure containing error code/description in case of 
 * failure
 * @return true if successful or false otherwise
 */
bool gru_create_dir(const char *path, gru_status_t *status);


/**
 * Given a path, this function will recursively create directories
 * @param path The path
 * @param status status structure containing error code/description in case of 
 * failure
 * @return true if successfully create the directories or false otherwise
 */
bool gru_create_dirs(const char *path, gru_status_t *status);

#ifdef __cplusplus
}
#endif

#endif /* GRU_PATH_H */

