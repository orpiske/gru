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

#ifndef GRU_UTIL_H
#define GRU_UTIL_H

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "collection/gru_list.h"
#include "common/gru_portable.h"
#include "string/gru_alt.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Removes spaces from the right side of a string
 * @param input Input string
 * @param size Size of the string
 * @return A pointer to the new string (which is the same address as input)
 */
gru_export char *gru_rtrim(char *input, size_t size);

/**
 * Removes spaces from the left side of a string
 * @param input Input string
 * @param size Size of the string
 * @return A pointer to the new string (which is the same address as input)
 */
gru_export char *gru_ltrim(char *input, size_t size);

/**
 * Removes spaces from all sides of a string
 * @param input Input string
 * @param size Size of the string
 * @return A pointer to the new string (which is the same address as input)
 */
gru_export char *gru_trim(char *input, size_t size);

/**
 * Given an URL, this function will return the file name for the download
 * @param url The url
 * @return the file name
 */
gru_export const char *gru_get_name_from_url(const char *url, size_t size);

/**
 * Split a string
 * @param str the string to split
 * @param set separator
 * @param status status object
 * @return a gru_list_t object where each element is a subpart of the original string
 * separated by d
 */
gru_export gru_list_t *gru_split(const char *str, char sep, gru_status_t *status);

/**
 * Cleans a string list returned by gru_split and free's the memory used by the strings
 * created for each sub-part
 * @param list the list to clean
 */
gru_export void gru_split_clean(gru_list_t *list);

/**
 * Serializes a string list
 * @param list
 * @param sep
 * @param status
 * @return
 */
char *gru_str_serialize(gru_list_t *list, char sep, gru_status_t *status);

#ifdef __cplusplus
}
#endif

#endif // GRU_UTIL_H
