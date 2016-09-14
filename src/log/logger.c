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
#include "logger.h"

static logger_t logger = NULL;
static log_level_t minimum = INFO;

void gru_logger_set(logger_t new_logger) {
	logger = new_logger;
}


logger_t gru_logger_get(void) {
	return logger;
}


void gru_logger_set_mininum(log_level_t new_minimum) {
    minimum = new_minimum;
}


log_level_t gru_logger_get_mininum() {
    return minimum;
}



bool gru_logger_can_log(log_level_t current)
{
    if (current >= minimum) {
        return true;
    }

    return false;
}



log_level_t gru_logger_get_level(const char *str) {
    if (strncasecmp("TRACE", str, strlen(str)) == 0) {
        return TRACE;
    }
    
    if (strncasecmp("DEBUG", str, strlen(str)) == 0) {
        return DEBUG;
    }
    
    if (strncasecmp("INFO", str, strlen(str)) == 0) {
        return INFO;
    }
        
    if (strncasecmp("WARNING", str, strlen(str)) == 0) {
        return WARNING;
    }
    
    if (strncasecmp("ERROR", str, strlen(str)) == 0) {
        return ERROR;
    }
    
    if (strncasecmp("FATAL", str, strlen(str)) == 0) {
        return FATAL;
    }
    
    if (strncasecmp("STAT", str, strlen(str)) == 0) {
        return STAT;
    }
    
    
    fprintf(stderr, "Invalid log level %s\n. Using INFO as default", str);
    return INFO;
}


void gru_logger_default_printer(log_level_t level, const char *msg, ...)
{
    if (!gru_logger_can_log(level)) {
        return;
    }

    va_list ap;
    char *ret = NULL;

    va_start(ap, msg);
    vasprintf(&ret, msg, ap);
    va_end(ap);


    switch (level) {
    case TRACE:
        fprintf(stderr, "[TRACE]: %s\n", ret);
        break;
    case DEBUG:
        fprintf(stderr, "[DEBUG]: %s\n", ret);
        break;
    case INFO:
        fprintf(stderr, "[INFO]: %s\n", ret);
        break;
    case STAT:
        fprintf(stderr, "[STAT]: %s\n", ret);
        break;
    case WARNING:
        fprintf(stderr, "[WARNING]: %s\n", ret);
        break;
    case ERROR:
        fprintf(stderr, "[ERROR]: %s\n", ret);
        break;
    case FATAL:
        fprintf(stderr, "[FATAL]: %s\n", ret);
        break;
    default:
        fprintf(stderr, "[MSG]: %s\n", ret);
        break;
    }

    free(ret);
}

