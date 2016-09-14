/**
 Copyright 2015 Otavio Rodolfo Piske
 
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <stdarg.h>

typedef enum log_level_t_ {
	TRACE = 0,
	DEBUG = 1,
	INFO = 2,
        STAT = 3,
	WARNING = 4,
	ERROR = 5,
	FATAL = 6,
} log_level_t;

typedef void(*logger_t)(log_level_t level, const char *message, ...);

/**
 * Gets the log level from an input string
 * @param str the input string (ie.: info, warn, etc)
 * @return the log level
 */
log_level_t gru_logger_get_level(const char *str);

/**
 * Whether can log (ie.: whether log level 1 is greater or equal to l2, thus 
 * allowing to log)
 * @param l1 log level being checked
 * @return 
 */
bool gru_logger_can_log(log_level_t l1);

/**
 * Sets the logger
 * @param logger the new logger
 */
void gru_logger_set(logger_t logger);

/**
 * Gets the logger
 * @return the logger
 */
logger_t gru_logger_get(void);

/**
 * Sets the minimum log level
 * @param minimum the minimum log level
 */
void gru_logger_set_mininum(log_level_t minimum);

/**
 * Gets the minimum log level
 * @return the minimum log level
 */
log_level_t gru_logger_get_mininum();


/**
 * Default logger that logs to stdout
 * @param level message level
 * @param msg the message + additional parameters
  */
void gru_logger_default_printer(log_level_t level, const char *msg, ...);

// GRU_LOGGER_H_
#endif
