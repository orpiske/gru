/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gru_path.h
 * Author: opiske
 *
 * Created on September 14, 2016, 7:29 PM
 */

#ifndef GRU_PATH_H
#define GRU_PATH_H

#include <string.h>
#include <stdbool.h>
#include <fcntl.h>

#include "common/gru_status.h"

#ifdef __cplusplus
extern "C" {
#endif

#define APPEND_SIZE_REMAP 64

bool gru_path_exists(const char *filename, gru_status_t *status);
bool gru_path_can_read_write(const char *filename, gru_status_t *status);
bool gru_path_rename_if_exists(const char *filename, gru_status_t *status);
char *gru_path_format(const char *dir, const char *name, gru_status_t *status);

#ifdef __cplusplus
}
#endif

#endif /* GRU_PATH_H */

