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
#include "gru_status.h"

void gru_status_set(gru_status_t *status, gru_status_code_t code,
                    const char *message, ...)
{
    assert(status);

    va_list ap;

    if (status->message != NULL) {
        gru_status_reset(status);
    }

    if (message != NULL) {
        va_start(ap, message);
        vasprintf(&status->message, message, ap);
        va_end(ap);
    }

    status->code = code;
}

void gru_status_reset(gru_status_t *status)
{
    free(status->message);
    status->message = NULL;
}

void gru_status_success(gru_status_t *status)
{
    gru_status_set(status, GRU_SUCCESS, NULL);
}

void gru_status_strerror(gru_status_t *status, gru_status_code_t code, int errnum)
{
    gru_status_reset(status);

    char *message = (char *) calloc(1, GRU_MAX_ERROR_MESSAGE);
    if (!message) {
        fprintf(stderr, "Not enough memory to allocate for the error message");

        return;
    }

    if (strerror_r(errnum, message, GRU_MAX_ERROR_MESSAGE) != 0) {
        switch (errno) {
        case EINVAL:
        {
            gru_status_set(status, GRU_FAILURE, "Invalid error number: %i",
                           errnum);


            goto e_exit;
        }
        case ERANGE:
        {
            gru_status_set(status, GRU_FAILURE,
                           "Insufficient buffer size for error message: %i",
                           errnum);

            goto e_exit;
        }
        default:
        {
            gru_status_set(status, GRU_FAILURE,
                           "Unknown error: %i",
                           errnum);

            goto e_exit;
        }
        }
    }

    gru_status_set(status, code, message);

    e_exit:
    free(message);

    return;
}