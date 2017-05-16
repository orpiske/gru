/**
 *    Copyright 2017 Otavio Rodolfo Piske <angusyoung@gmail.com>
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#ifndef GRU_UNITS_H
#define GRU_UNITS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert an arbitrary value to kb
 */
static inline uint64_t gru_unit_kb(uint64_t num) {
	return (num / 1024);
}


/**
 * Convert an arbitrary value to mb
 */
static inline uint64_t gru_unit_mb(uint64_t num) {
	return gru_unit_kb(num) / 1024;
}


/**
 * Convert an arbitrary value to gb
 */
static inline uint64_t gru_unit_gb(uint64_t num) {
	return gru_unit_mb(num) / 1024;
}

#ifdef __cplusplus
}
#endif


#endif /* GRU_UNITS_H */
