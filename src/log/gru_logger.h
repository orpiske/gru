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

#ifndef GRU_LOGGER_H_
#define GRU_LOGGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(_WIN32) && !defined(_WIN64)
#include <strings.h>
#endif

#include <stdarg.h>
#include <stdbool.h>

#include "common/gru_base.h"
#include "time/gru_time_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum log_level_t_ {
	GRU_TRACE = 0,
	GRU_DEBUG = 1,
	GRU_INFO = 2,
	GRU_WARNING = 4,
	GRU_ERROR = 5,
	GRU_FATAL = 6,
} log_level_t;

typedef void (*logger_t)(log_level_t level, const char *message, ...);

/**
 * Gets the log level from an input string
 * @param str the input string (ie.: info, warn, etc)
 * @return the log level
 */
gru_export log_level_t gru_logger_get_level(const char *str);

/**
 * Whether can log (ie.: whether log level 1 is greater or equal to l2, thus
 * allowing to log)
 * @param l1 log level being checked
 * @return
 */
gru_export bool gru_logger_can_log(log_level_t l1);

/**
 * Sets the logger
 * @param logger the new logger
 */
gru_export void gru_logger_set(logger_t logger);

/**
 * Gets the logger
 * @return the logger
 */
gru_export logger_t gru_logger_get(void);

/**
 * Sets the minimum log level
 * @param minimum the minimum log level
 */
gru_export void gru_logger_set_mininum(log_level_t minimum);

/**
 * Gets the minimum log level
 * @return the minimum log level
 */
gru_export log_level_t gru_logger_get_mininum();

/**
 * Default logger that logs to stdout
 * @param level message level
 * @param msg the message + additional parameters
  */
gru_export void gru_logger_default_printer(log_level_t level, const char *msg, ...);

/**
 * Utility printing function that can be used by implementations of the logger printer
 * @param level message level
 * @param msg the message + additional parameters
 * @param ap va_list object for variable argument list
  */
gru_export void
	gru_logger_default_do_print(log_level_t level, const char *msg, va_list ap);


/**
 * A simple logger that logs to stderr including the time when the even happened
 * @param level message level
 * @param msg the message + additional parameters
  */
gru_export void gru_logger_timed_printer(log_level_t level, const char *msg, ...);

/**
 * Utility printing function that can be used by implementations of the timed logger printer
 * @param level message level
 * @param msg the message + additional parameters
 * @param ap va_list object for variable argument list
  */
gru_export void gru_logger_timed_do_print(log_level_t level, const char *msg, va_list ap);

#ifdef __cplusplus
}
#endif

// GRU_LOGGER_H_
#endif
