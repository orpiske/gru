/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ioutils.h
 * Author: otavio
 *
 * Created on July 5, 2016, 11:23 AM
 */

#ifndef GRU_IOUTILS_H
#define GRU_IOUTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "gru_path.h"
#include "common/gru_status.h"



#ifdef __cplusplus
extern "C" {
#endif

bool gru_io_remap(const char *dir, const char *name, FILE *fd, gru_status_t *status);
FILE *gru_io_open_file(const char *dir, const char *name, gru_status_t *status);

#ifdef __cplusplus
}
#endif

#endif /* GRU_IOUTILS_H */

