/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "gru_path.h"

/**
 * Checks whether a given file exists
 * @param filename the filename
 * @return
 */
bool gru_path_exists(const char *filename, gru_status_t *status)
{
    int ret = 0;
    struct stat info;

    ret = stat(filename, &info);
    if (ret == 0) {

        if (status) {
            gru_status_reset(status);
        }

        return true;
    }
    else {
        if (status) {
            gru_status_strerror(status, GRU_FAILURE, errno);
        }
    }

    return false;
}


/**
 * Checks whether can read/write a given file
 * @param filename the filename
 * @return
 */
bool gru_path_can_read_write(const char *filename, gru_status_t *status)
{
    int ret = 0;


    ret = access(filename, R_OK | W_OK);
    if (ret < 0) {
        switch (errno) {
        case ENOENT:
        {
            gru_status_set(status, GRU_FAILURE,
                           "No such file or directory %s: %s",
                           filename, strerror(errno));

            return false;
        }
        case EACCES:
        {
            gru_status_set(status, GRU_FAILURE,
                           "Access denied (no read/write permission) %s: %s",
                           filename, strerror(errno));
            return false;
        }
        default:
        {
            gru_status_strerror(status, GRU_FAILURE, errno);
            return false;
        }
        }
    }

    return true;
}


bool gru_path_rename_if_exists(const char *filename, gru_status_t *status)
{
    if (!gru_path_exists(filename, status)) {
        return true;
    }

    if (!gru_path_can_read_write(filename, status)) {
        return false;
    }

    int size = strlen(filename) + 16;
    char *new_file = (char *) malloc(size);

    if (!new_file) {
        gru_status_set(status, GRU_FAILURE,
               "Not enough memory to allocate for renaming the existing file");
        return false;
    }

    int i = 0;
    do {
        bzero(new_file, size);
        snprintf(new_file, size, "%s.%03i", filename, i);

        if (!gru_path_exists(new_file, status)) {
            int ret = 0;

            ret = rename(filename, new_file);
            if (ret != 0) {
                gru_status_strerror(status, GRU_FAILURE, errno);

                free(new_file);
                return false;
            }

            break;
        }
        i++;
    }
    while (true);

    free(new_file);
    return true;
}

char *gru_path_format(const char *dir, const char *name, gru_status_t *status)
{
    char *fullpath;
    size_t size = strlen(dir) + APPEND_SIZE_REMAP;
    
    fullpath = (char *) malloc(size);
    if (fullpath == NULL) {
        gru_status_set(status, GRU_FAILURE, "Unable to format path");
        

        free(fullpath);
        return NULL;
    }

    bzero(fullpath, size);
    snprintf(fullpath, size - 1, "%s/%s", dir, name);

    return fullpath;
}