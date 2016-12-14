/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "gru_alloc.h"


void *gru_alloc(size_t size, gru_status_t *status) {
    void *ret = calloc(1, size);
    
    if (unlikely(ret == NULL)) {
        gru_status_set(status, GRU_FAILURE, 
                       "Unable to allocate memory for GRU object");
        
        return NULL;
    }
    
    return ret;
}

void gru_dealloc(void **obj) {
    free(*(obj));
    *obj= NULL;
}

inline void gru_dealloc_string(char **obj) {
    gru_dealloc((void **)obj);
}

inline void gru_dealloc_const_string(const char **obj) {
    gru_dealloc((void **)obj);
}