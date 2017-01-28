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
#ifndef GRU_TIME_UTILS_H
#define GRU_TIME_UTILS_H

#include <ctype.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#if !defined(_WIN32) && !defined(_WIN64)
#include <sys/time.h>
#include <unistd.h>
#else
#include <windows.h>
#endif

#include "common/gru_alloc.h"
#include "common/gru_portable.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An alias to struct timeval
 */
typedef struct timeval gru_timestamp_t;

/**
 * Add seconds to a timestamp object
 * @param t timestamp
 * @param count number of seconds to add
 */
gru_export void gru_time_add_seconds(gru_timestamp_t *t, uint64_t count);

/**
 * Add minutes to a timestamp object
 * @param t timestamp
 * @param count number of minutes to add
 */
gru_export void gru_time_add_minutes(gru_timestamp_t *t, uint64_t count);

/**
 * Read a string in the format seconds.microseconds and return a struct timeval
 * @param str The string in the format seconds.microseconds
 * @return a timestamp object with the parsed data
 */
gru_export gru_timestamp_t gru_time_read_str(const char *str);

/**
 * Write a timeval structure to a string.
 * @param t the timeval structure
 * @return A string that must be free'd after use
 */
gru_export char *gru_time_write_str(const gru_timestamp_t *t);

/**
 * Gets the current moment in time
 * @return a timestamp object with the current point in time
 */
gru_export gru_timestamp_t gru_time_now();

/**
 * Converts an unformatted string of milliseconds since epoch to a timespamp
 * @param ts A numeric string representing the milliseconds since epoch (ie.:
 * 1484719545264)
 * @return a timestamp object with the parsed data
 */
gru_export gru_timestamp_t gru_time_from_milli_char(const char *ts);

/**
 * Converts milliseconds since epoch to a timestamp
 * @param timestamp milliseconds since Epoch
 * @return a timestamp object with the converted data
 */
gru_export gru_timestamp_t gru_time_from_milli(int64_t timestamp);

#ifdef __cplusplus
}
#endif

#endif /* GRU_TIME_UTILS_H */
