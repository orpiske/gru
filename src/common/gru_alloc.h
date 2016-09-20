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
    
void *gru_alloc(size_t size, gru_status_t *status);
void gru_dealloc(void **obj);
void gru_dealloc_string(char **obj);

#define gru_alloc_check(obj, ret) if (obj == NULL) return ret;

#ifdef __cplusplus
}
#endif

#endif /* GRU_ALLOC_H */

