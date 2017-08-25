/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   gru_alloc.h
 * Author: opiske
 *
 * Created on September 20, 2016, 2:43 PM
 */

#ifndef GRU_ALLOC_H
#define GRU_ALLOC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gru_base.h"
#include "gru_status.h"

/**
 * Allocate a block of memory
 * @param size the amount of memory (in bytes) to allocate
 * @param status a status pointer that will be set in case of failure
 * @return a pointer to the newly allocated memory or NULL if failed
 */
gru_export void *gru_alloc(size_t size, gru_status_t *status);

/**
 * Deallocate a block of memory and set its pointer to NULL
 * @param obj a pointer to a pointer of block of memory to deallocate
 */
gru_export void gru_dealloc(void **obj);

/**
 * Deallocate a block of memory used by a char * and set its pointer to NULL
 * @param obj a pointer to a pointer of block of memory to deallocate
 */
gru_export void gru_dealloc_string(char **obj);

/**
 * Deallocate a block of memory used by a const char * and set its pointer to NULL
 * @param obj a pointer to a pointer of block of memory to deallocate
 */
gru_export void gru_dealloc_const_string(const char **obj);

/**
 * Check whether the allocation was successfull otherwise return whatever set as ret
 */
#define gru_alloc_check(obj, ret)                                                        \
	if ((obj) == NULL)                                                                     \
		return ret;

#ifdef __cplusplus
}
#endif

#endif /* GRU_ALLOC_H */
