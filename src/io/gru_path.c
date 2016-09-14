/**
 Copyright 2016 Otavio Rodolfo Piske
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */
#include "gru_path.h"


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

bool gru_path_rename_cond(const char *filename, gru_path_cond_t cond, 
                          gru_status_t *status)
{
    
    // Return if the condition is already fulfilled
    if (!cond(filename, status)) {
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

        if (!cond(new_file, status)) {
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


bool gru_path_rename(const char *filename, gru_status_t *status)
{
    return gru_path_rename_cond(filename, gru_path_exists, status);
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