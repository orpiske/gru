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
#ifndef GRU_STATUS_H
#define GRU_STATUS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "common/gru_portable.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GRU_MAX_ERROR_MESSAGE 1024

/*
 * Valid status codes
 */
typedef enum gru_status_code_t_ {
    GRU_SUCCESS,
    GRU_FAILURE,
} gru_status_code_t;


/**
 * Status type
 */
typedef struct gru_status_t_ {
    gru_status_code_t code;
    char *message;
} gru_status_t;

/**
 * Sets the status
 * @param status an instance of the status object to set
 * @param code the code to set the object to
 * @param message the status message followed by any other parameter as accepted
 * by vasprintf
 */
gru_export void gru_status_set(gru_status_t *status, gru_status_code_t code,
                      const char *message, ...);

/**
 * Sets the status from the errno
 * @param status an instance of the status object to set
 * @param code the code to set the object to
 * @param errnum the error number (as in errno)
 */
gru_export void gru_status_strerror(gru_status_t *status, gru_status_code_t code,
                         int errnum);

/**
 * Resets the status
 * @param status an instance of the status object to set
 */
gru_export void gru_status_reset(gru_status_t *status);

/**
 * Sets the status to success
 * @param status an instance of the status object to set
 */
gru_export void gru_status_success(gru_status_t *status);


#ifdef __cplusplus
}
#endif

#endif /* GRU_STATUS_H */
