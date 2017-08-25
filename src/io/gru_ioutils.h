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
#ifndef GRU_IOUTILS_H
#define GRU_IOUTILS_H

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>

#if !defined(_WIN32) && !defined(_WIN64)
#include <unistd.h>
#else
#include <io.h>
#endif
#include <stdarg.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>

#include "common/gru_portable.h"
#include "common/gru_status.h"
#include "gru_path.h"

/**
 * @brief IO utilities. Lot's of nonsense here. Most will be fixed/rewritten in
 * the future.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Remaps IO from one file descriptor to a file pointed by dir/name
 * @param dir directory of the file
 * @param name name of the file
 * @param fd file descriptor to remap
 * @param status status structure containing error code/description in case of
 * failure
 * @return true if remapped or false otherwise (in this case, check status)
 */
gru_export bool
	gru_io_remap(const char *dir, const char *name, FILE *fd, gru_status_t *status);

/**
 * Tries to safely open a file (ie.: creating directories and stuff). Truncates
 * the file
 * @param dir directory of the file
 * @param name name of the file
 * @param status status structure containing error code/description in case of
 * failure
 * @return a FILE descriptor for the opened file or NULL otherwise (in this case,
 * check status)
 */
gru_export FILE *
	gru_io_open_file(const char *dir, const char *name, gru_status_t *status);

/**
 * Tries to safely open a file (ie.: creating directories and stuff). Truncates
 * the file
 * @param path path to the file
 * @param status status structure containing error code/description in case of
 * failure
 * @return a FILE descriptor for the opened file or NULL otherwise (in this case,
 * check status)
 */
gru_export FILE *gru_io_open_file_path(const char *path, gru_status_t *status);

/**
 * Tries to safely open a file (ie.: creating directories and stuff)
 * @param dir directory of the file
 * @param name name of the file
 * @param status status structure containing error code/description in case of
 * failure
 * @return a FILE descriptor for the opened file or NULL otherwise (in this case,
 * check status)
 */
gru_export FILE *
	gru_io_open_file_read(const char *dir, const char *name, gru_status_t *status);

/**
 * Tries to safely open a file (ie.: creating directories and stuff)
 * @param path path to the file
 * @param status status structure containing error code/description in case of
 * failure
 * @return a FILE descriptor for the opened file or NULL otherwise (in this case,
 * check status)
 */
gru_export FILE *gru_io_open_file_read_path(const char *path, gru_status_t *status);

/**
 * Tries to safely open a file (ie.: creating directories and stuff)
 * @param dir directory of the file
 * @param name name of the file
 * @param status status structure containing error code/description in case of
 * failure
 * @return a FILE descriptor for the opened file or NULL otherwise (in this case,
 * check status)
 */
gru_export FILE *
	gru_io_open_unique_file(const char *dir, const char *name, gru_status_t *status);

/**
 * Reads the file pointed by file into the destination buffer. The memory for
 * the allocation buffer is allocated as needed and must be free'd after use
 * @param dest the destination buffer
 * @param file the file to read
 * @param status status structure containing error code/description in case of
 * failure
 * @return the amount of bytes read of 0 in case of error
 */
gru_export size_t gru_io_read_text_into(char **dest, FILE *file, gru_status_t *status);

#ifdef __cplusplus
}
#endif

#endif /* GRU_IOUTILS_H */
