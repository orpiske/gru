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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

/**
 * Removes spaces from the right side of a string
 * @param input Input string
 * @param size Size of the string
 * @return A pointer to the new string (which is the same address as input)
 */
char *gru_rtrim(char *input, int size);

/**
 * Removes spaces from the left side of a string
 * @param input Input string
 * @param size Size of the string
 * @return A pointer to the new string (which is the same address as input)
 */
char *gru_ltrim(char *input, int size);

/**
 * Removes spaces from all sides of a string
 * @param input Input string
 * @param size Size of the string
 * @return A pointer to the new string (which is the same address as input)
 */
char *gru_trim(char *input, int size);


/**
 * Given an URL, this function will return the file name for the download
 * @param url The url
 * @return the file name
 */
const char *gru_get_name_from_url(const char *url, int size);

#endif // GRU_UTIL_H
