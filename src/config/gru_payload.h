/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gru_payload.h
 * Author: opiske
 *
 * Created on September 19, 2016, 4:35 PM
 */

#ifndef GRU_PAYLOAD_H
#define GRU_PAYLOAD_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "common/gru_status.h"
#include "io/gru_path.h"
#include "io/gru_ioutils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*gru_payload_data_init_t)(void *);
typedef void(*gru_payload_data_save_t)(FILE *, void *);
typedef void(*gru_payload_data_read_t)(FILE *, void *);

typedef struct gru_payload_t_ {
    gru_payload_data_init_t init;
    gru_payload_data_save_t save;
    gru_payload_data_read_t read;
    
    void *data;
} gru_payload_t;

gru_payload_t *gru_payload_init(gru_payload_data_init_t init, 
                                        gru_payload_data_save_t save,
                                        gru_payload_data_read_t read,
                                        void *data,
                                        gru_status_t *status);

void gru_payload_destroy(gru_payload_t **payload);

void gru_payload_init_data(gru_payload_t *payload, const char *dir, 
                           const char *name,
                           FILE **file, 
                           gru_status_t *status);

#ifdef __cplusplus
}
#endif

#endif /* GRU_PAYLOAD_H */

