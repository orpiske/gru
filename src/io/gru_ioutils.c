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
#include "gru_ioutils.h"


bool gru_io_remap(const char *dir, const char *name, FILE *fd, 
                  gru_status_t *status)
{
    char *fullpath = gru_path_format(dir, name, status);
    
    if (!fullpath) {
        return false;
    }

    if (!gru_path_rename(fullpath, status)) {
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

    if (!gru_path_exists(fullpath, status) && (status->code == GRU_SUCCESS)) {
        if (!gru_create_dirs(dir, status)) {
            return NULL;
        }
    }
    
    FILE *f = fopen(fullpath, "w+");
    if (f == NULL) {
        gru_status_strerror(status, GRU_FAILURE, errno);

        free(fullpath);
        return NULL;
    }

    free(fullpath);
    return f;
}


FILE *gru_io_open_file_read(const char *dir, const char *name, gru_status_t *status)
{

    char *fullpath = gru_path_format(dir, name, status);

    if (!gru_path_exists(fullpath, status) && (status->code == GRU_SUCCESS)) {
        if (!gru_create_dirs(dir, status)) {
            return NULL;
        }
    }
    
    FILE *f = fopen(fullpath, "r+");
    if (f == NULL) {
        gru_status_strerror(status, GRU_FAILURE, errno);

        free(fullpath);
        return NULL;
    }

    free(fullpath);
    return f;
}


FILE *gru_io_open_unique_file(const char *dir, const char *name, gru_status_t *status)
{

    char *fullpath = gru_path_format(dir, name, status);

    if (!gru_path_rename(fullpath, status)) {
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