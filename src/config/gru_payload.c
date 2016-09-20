/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "gru_payload.h"

gru_payload_t *gru_payload_init(gru_payload_data_init_t init, 
                                        gru_payload_data_save_t save,
                                        gru_payload_data_read_t read,
                                        void *data,
                                        gru_status_t *status)
{
    gru_payload_t *ret = (gru_payload_t *) malloc(sizeof(gru_payload_t));
    
    if (!ret) {
        gru_status_set(status, GRU_FAILURE, 
                       "Unable to allocate memory for the payload");
        return NULL;
    }
    
    ret->init = init;
    ret->save = save; 
    ret->read = read;
    ret->data = data;
    
    return ret;
}


void gru_payload_destroy(gru_payload_t **payload) {
    free(*payload);
    *payload = NULL;
}

void gru_payload_init_data(gru_payload_t *payload, const char *dir, 
                           const char *name, FILE **file, 
                           gru_status_t *status)
{
    char *fullpath = gru_path_format(dir, name, status);
    
    if (!gru_path_exists(fullpath, status) && status->code == GRU_SUCCESS) {
        (*file) = gru_io_open_file(dir, name, status);
        if (!(*file)) {
            return;
        }
        
        // set defaults
        payload->init(payload->data);

        // write configs
        payload->save((*file), payload->data);
        
        fflush(NULL);
    }
    else {
        if (status->code != GRU_SUCCESS) {
            return;
        }
        
        (*file) = gru_io_open_file_read(dir, name, status);
        if (!(*file)) {
            return;
        }
        
        payload->read((*file), payload->data);
    }   
}