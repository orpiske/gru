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
#ifndef GRU_ALT_H
#define GRU_ALT_H

#include <string.h>

#include "common/gru_base.h"
#include "common/gru_portable.h"

/**
 * @brief Very simple alternatives to some safer string variables. Do not use unless
 * libbsd or other more mature alternatives are not available
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAVE_STRLCPY

/**
 * Poor man's implementation of strlcpy (works just like strncpy, but copies size - 1)
 * @param dst destination buffer
 * @param src source buffer
 * @param size amount of bytes to copy
 * @return The amount of bytes copied
 */
size_t strlcpy(char *gru_restrict dst, const char *gru_restrict src, size_t size);

/**
 * Poor man's implementation of strlcat
 * @param dst destination buffer
 * @param src source buffer
 * @param size amount of bytes to copy
 * @return The total length of the string they tried to create
 */
size_t strlcat(char *gru_restrict dst, const char *gru_restrict src, size_t size);

#endif // HAVE_STRLCPY

#ifdef __cplusplus
}
#endif

#endif /* GRU_ALT_H */
