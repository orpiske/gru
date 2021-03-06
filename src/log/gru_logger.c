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
#include "gru_logger.h"

static logger_t logger = NULL;
static log_level_t minimum = GRU_INFO;

void gru_logger_set(logger_t new_logger) {
	logger = new_logger;
}

logger_t gru_logger_get(void) {
	return logger;
}

void gru_logger_set_minimum(log_level_t new_minimum) {
	minimum = new_minimum;
}

log_level_t gru_logger_get_minimum() {
	return minimum;
}

bool gru_logger_can_log(log_level_t current) {
	if (current >= minimum) {
		return true;
	}

	return false;
}

log_level_t gru_logger_get_level(const char *str) {
	if (strncasecmp("TRACE", str, 5) == 0) {
		return GRU_TRACE;
	}

	if (strncasecmp("DEBUG", str, 5) == 0) {
		return GRU_DEBUG;
	}

	if (strncasecmp("INFO", str, 4) == 0) {
		return GRU_INFO;
	}

	if (strncasecmp("WARNING", str, 7) == 0) {
		return GRU_WARNING;
	}

	if (strncasecmp("ERROR", str, 5) == 0) {
		return GRU_ERROR;
	}

	if (strncasecmp("FATAL", str, 5) == 0) {
		return GRU_FATAL;
	}

	fprintf(stderr, "Invalid log level %s.\n Using INFO as default\n", str);
	return GRU_INFO;
}

void gru_logger_default_printer(log_level_t level, const char *msg, ...) {
	if (!gru_logger_can_log(level)) {
		return;
	}

	va_list ap;

	va_start(ap, msg);
	gru_logger_default_do_print(level, msg, ap);
	va_end(ap);
}

void gru_logger_default_do_print(log_level_t level, const char *msg, va_list ap) {
	switch (level) {
		case GRU_TRACE:
			fprintf(stderr, "[TRACE]: ");
			break;
		case GRU_DEBUG:
			fprintf(stderr, "[DEBUG]: ");
			break;
		case GRU_INFO:
			fprintf(stderr, "[INFO]: ");
			break;
		case GRU_WARNING:
			fprintf(stderr, "[WARNING]: ");
			break;
		case GRU_ERROR:
			fprintf(stderr, "[ERROR]: ");
			break;
		case GRU_FATAL:
			fprintf(stderr, "[FATAL]: ");
			break;
		default:
			fprintf(stderr, "[MSG]: ");
			break;
	}

	// TODO: this is possibly unsafe and should be replaced with something safer in the
	// future
	vfprintf(stderr, msg, ap);
	fprintf(stderr, "\n");
}


void gru_logger_timed_printer(log_level_t level, const char *msg, ...) {
	if (!gru_logger_can_log(level)) {
		return;
	}

	va_list ap;

	va_start(ap, msg);
	gru_logger_timed_do_print(level, msg, ap);
	va_end(ap);
}


void gru_logger_timed_do_print(log_level_t level, const char *msg, va_list ap) {
	gru_timestamp_t now = gru_time_now();
	gru_status_t status = gru_status_new();

	char *str = gru_time_write_format(&now, "%Y-%m-%d %H:%M:%S", &status);
	if (unlikely(!str)) {
		fprintf(stderr, "NOMEM ");
	}
	else {
		uint32_t milli = (uint32_t) now.tv_usec / 1000;

		fprintf(stderr, "%s.%03"PRId32" ", str, milli);
		gru_dealloc_string(&str);
	}

	switch (level) {
	case GRU_TRACE:
		fprintf(stderr, "TRACE: ");
		break;
	case GRU_DEBUG:
		fprintf(stderr, "DEBUG: ");
		break;
	case GRU_INFO:
		fprintf(stderr, "INFO: ");
		break;
	case GRU_WARNING:
		fprintf(stderr, "WARNING: ");
		break;
	case GRU_ERROR:
		fprintf(stderr, "ERROR: ");
		break;
	case GRU_FATAL:
		fprintf(stderr, "FATAL: ");
		break;
	default:
		fprintf(stderr, "MSG: ");
		break;
	}

	// TODO: this is possibly unsafe and should be replaced with something safer in the
	// future
	vfprintf(stderr, msg, ap);
	fprintf(stderr, "\n");
}