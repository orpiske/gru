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


gru_path_t *gru_path_init_from_slice(const char *directory, const char *filename, 
                                     gru_status_t *status) {
    gru_path_t *ret = gru_alloc(sizeof(gru_path_t), status);
    
    gru_alloc_check(ret, NULL);
    
    asprintf(&ret->location.slice.directory, "%s", directory);
    asprintf(&ret->location.slice.filename, "%s", filename);
    ret->type = SLICE;
    
    return ret;
}

gru_path_t *gru_path_init_from_path(const char *fullpath, gru_status_t *status) {
    gru_path_t *ret = gru_alloc(sizeof(gru_path_t), status);
    
    gru_alloc_check(ret, NULL);
    
    asprintf(&ret->location.full.fullpath, "%s", fullpath);
    ret->type = FULL;
    
    return ret;
}

void gru_path_destroy(gru_path_t **path) {
    if ((*path)->type == SLICE) {
        gru_dealloc_string(&(*path)->location.slice.directory);
        gru_dealloc_string(&(*path)->location.slice.filename);
    }
    else {
        gru_dealloc_string(&(*path)->location.full.fullpath);
    }
    
    gru_dealloc((void **) path);
}

static bool gru_path_exists_internal(const char *filename, gru_status_t *status)
{
    int ret = 0;
    struct stat info;

    ret = stat(filename, &info);
    if (ret == 0) {
        return true;
    }
    else {
        if (errno == ENOENT) {
            return false;
        }
        else {
            if (status) {
                gru_status_strerror(status, GRU_FAILURE, errno);
            }
        }
    }

    return false;
}

bool gru_path_exists(const gru_path_t *path, gru_status_t *status) {
    if (path->type == SLICE) {
        char *fullpath = gru_path_format(path->location.slice.directory, 
                                         path->location.slice.filename, status);
        
        bool ret = gru_path_exists_internal(fullpath, status);
        gru_dealloc_string(&fullpath);
        
        return ret;
    }
    
    return gru_path_exists_internal(path->location.full.fullpath, status);
}

bool gru_path_fexists(int fd, gru_status_t *status) {
    int ret = 0;
    struct stat info;

    ret = fstat(fd, &info);
    if (ret == 0) {
        return true;
    }
    else {
        if (errno == ENOENT) {
            return false;
        }
        else {
            if (status) {
                gru_status_strerror(status, GRU_FAILURE, errno);
            }
        }
    }

    return false;
}

static bool gru_path_can_read_write_internal(const char *filename, gru_status_t *status)
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

bool gru_path_can_read_write(const gru_path_t *path, gru_status_t *status) {
    if (path->type == SLICE) {
        char *fullpath = gru_path_format(path->location.slice.directory, 
                                         path->location.slice.filename, status);
        
        bool ret = gru_path_can_read_write_internal(fullpath, status);
        gru_dealloc_string(&fullpath);
        
        return ret;
    }
    
    return gru_path_can_read_write_internal(path->location.full.fullpath, status);
}

static bool gru_path_rename_cond_internal(const char *filename, gru_path_cond_t cond,
                          gru_status_t *status)
{

    // Return if the condition is already fulfilled
    if (!cond(filename, status)) {
        return true;
    }

    if (!gru_path_can_read_write_internal(filename, status)) {
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

bool gru_path_rename_cond(const gru_path_t *path, gru_path_cond_t cond,
                          gru_status_t *status)
{
    if (path->type == SLICE) {
        char *fullpath = gru_path_format(path->location.slice.directory, 
                                         path->location.slice.filename, status);
        
        bool ret = gru_path_rename_cond_internal(fullpath, cond, status);
        gru_dealloc_string(&fullpath);
        
        return ret;
    }
    
    return gru_path_rename_cond_internal(path->location.full.fullpath, cond,
                                            status);
}

bool gru_path_rename(const gru_path_t *path, gru_status_t *status)
{
    return gru_path_rename_cond(path, gru_path_exists_internal, status);
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

static bool gru_create_dir_internal(const char *path, gru_status_t *status)
{
    int ret = 0;

    ret = mkdir(path, 0774);
    if (ret != 0) {

        gru_status_strerror(status, GRU_FAILURE, errno);
        return false;
    }

    return true;
}

bool gru_create_dir(const gru_path_t *path, gru_status_t *status) {
    if (path->type == SLICE) {
        char *fullpath = gru_path_format(path->location.slice.directory, 
                                         path->location.slice.filename, status);
        
        bool ret = gru_create_dir_internal(fullpath, status);
        gru_dealloc_string(&fullpath);
        
        return ret;
    }
    
    return gru_create_dir_internal(path->location.full.fullpath, status);
}


static bool gru_create_dirs_internal(const char *path, gru_status_t *status)
{
    const char *ptr = path;
    int count = 0;
    int tmp_size = strlen(path) + 1;
    char *tmp = (char *) malloc(tmp_size);

    if (!tmp) {
        gru_status_set(status, GRU_FAILURE,
                       "Not enough memory to allocate %i bytes", tmp_size);

        return false;
    }

    bzero(tmp, tmp_size);
    do {
        const char *last = ptr;

        ptr++;
        ptr = strstr(ptr, FILE_SEPARATOR);
        count += ptr - last;

        snprintf(tmp, tmp_size, "%.*s", count, path);

        if (gru_path_exists_internal(tmp, status)) {
            continue;
        }

        if (!gru_create_dir_internal(tmp, status)) {
            free(tmp);

            return false;
        }
    }
    while (ptr != NULL);

    free(tmp);
    return true;
}


bool gru_create_dirs(const gru_path_t *path, gru_status_t *status) {
    if (path->type == SLICE) {
        char *fullpath = gru_path_format(path->location.slice.directory, 
                                         path->location.slice.filename, status);
        
        bool ret = gru_create_dirs_internal(fullpath, status);
        gru_dealloc_string(&fullpath);
        
        return ret;
    }
    
    return gru_create_dirs_internal(path->location.full.fullpath, status);
}

