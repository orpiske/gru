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
#ifndef GRU_TIME_UTILS_H
#define GRU_TIME_UTILS_H

#include <ctype.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#if !defined(_WIN32) && !defined(_WIN64)
#include <sys/time.h>
#include <unistd.h>
#else
#include <windows.h>

#include "time/other/gru_time_portable.h"

#endif

#include "common/gru_alloc.h"
#include "common/gru_portable.h"
#include "gru_localtime.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Maximum size for the second part for a GRU-parseable timestamp string */
#define GRU_TS_STRING_SEC_MAX 16

/** Maximum size for the microsecond part for a GRU-parseable timestamp string */
#define GRU_TS_STRING_USEC_MAX 7

/** Maximum size for a GRU-parseable timestamp string (ie.: seconds.microseconds) */
#define GRU_TS_STRING_MAX GRU_TS_STRING_SEC_MAX + GRU_TS_STRING_USEC_MAX + 1

/**
 * An alias to struct timeval
 */
typedef struct timeval gru_timestamp_t;

/**
 * Add microseconds to a timestamp object
 * @param t timestamp
 * @param count number of microtseconds to add
 */
void gru_time_add_microseconds(gru_timestamp_t *t, uint64_t count);

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
 * Add hours to a timestamp object
 * @param t timestamp
 * @param count number of hours to add
 */
gru_export void gru_time_add_hours(gru_timestamp_t *t, uint64_t count);

/**
 * Add days to a timestamp object
 * @param t timestamp
 * @param count number of days to add
 */
gru_export void gru_time_add_days(gru_timestamp_t *t, uint64_t count);

/**
 * Read a string in the format seconds.microseconds and return a struct timeval. The
 * microseconds represents the fraction of the seconds value and should not be equal or
 * greater than 1000000. Otherwise, the code will only consider the first 6 bytes of the
 * microseconds string.
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
 * Writes the input timestamp value according to the given format
 * @param t Input timestamp structure
 * @param format output format
 * @param status status structure that may contain error details in case of failure
 * @return A pointer to a formatted string or NULL in case of failure. The returned string
 * must be free'd after use
 */
gru_export char *gru_time_write_format(const gru_timestamp_t *t,
	const char *format,
	gru_status_t *status);

/**
 * Gets the current moment in time
 * @return a timestamp object with the current point in time
 */
gru_export gru_timestamp_t gru_time_now();

/**
 * Gets the current moment in time in milliseconds
 * @return current time in milliseconds since Epoch
 */
gru_export uint64_t gru_time_now_milli();

/**
 * Converts an unformatted string of milliseconds since epoch to a timestamp
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

/**
 * Converst a timestamp to milliseconds
 * @param ts A pointer to a timestamp structure
 * @return the timestamp as a milliseconds since epoch
 */
gru_export uint64_t gru_time_to_milli(const gru_timestamp_t *ts);

/**
 * Calculates the elapsed time between two timestamps
 * @param start Start time
 * @param end End time
 * @note The behavior is undefined if the end time is smaller than the start time
 * @return The elapsed time in seconds
 */
gru_export uint64_t gru_time_elapsed_secs(gru_timestamp_t start, gru_timestamp_t end);


/**
 * Calculates the elapsed time between two timestamps
 * @param start Start time
 * @param end End time
 * @note The behavior is undefined if the end time is smaller than the start time
 * @return The elapsed time in milliseconds
 */
gru_export uint64_t gru_time_elapsed_milli(gru_timestamp_t start, gru_timestamp_t end);

#ifdef __cplusplus
}
#endif

#endif /* GRU_TIME_UTILS_H */
