/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "gru_ioutils.h"


bool gru_io_remap(const char *dir, const char *name, FILE *fd, 
                  gru_status_t *status)
{
    char *fullpath = gru_path_format(dir, name, status);
    
    if (!fullpath) {
        return false;
    }

    if (!gru_path_rename_if_exists(fullpath, status)) {
        free(fullpath);
        return false;
    }

    FILE *f = freopen(fullpath, "a", fd);
    if (f == NULL) {
        gru_status_strerror(status, GRU_FAILURE, errno);

        free(fullpath);
        return false;
    }

    free(fullpath);
    return true;
}


FILE *gru_io_open_file(const char *dir, const char *name, gru_status_t *status)
{

    char *fullpath = gru_path_format(dir, name, status);

    if (!gru_path_rename_if_exists(fullpath, status)) {
        free(fullpath);
        return NULL;
    }


    FILE *f = fopen(fullpath, "w+");
    if (f == NULL) {
        gru_status_strerror(status, GRU_FAILURE, errno);

        free(fullpath);
        return false;
    }

    free(fullpath);
    return f;
}