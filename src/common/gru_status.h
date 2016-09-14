/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gru_status.h
 * Author: opiske
 *
 * Created on September 14, 2016, 10:03 AM
 */

#ifndef GRU_STATUS_H
#define GRU_STATUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
    
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
void gru_status_set(gru_status_t *status, gru_status_code_t code, 
                      const char *message, ...);

/**
 * Sets the status from the errno
 * @param status an instance of the status object to set
 * @param code the code to set the object to
 * @param errnum the error number (as in errno)
 */
void gru_status_strerror(gru_status_t *status, gru_status_code_t code, 
                         int errnum);

/**
 * Resets the status
 * @param status an instance of the status object to set
 */
void gru_status_reset(gru_status_t *status);

/**
 * Sets the status to success
 * @param status an instance of the status object to set
 */
void gru_status_success(gru_status_t *status);


#ifdef __cplusplus
}
#endif

#endif /* GRU_STATUS_H */

