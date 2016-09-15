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
#include "gru_config.h"


gru_config_t *gru_config_init(const char *dir, const char *filename, 
                              void *payload, gru_status_t *status) {
    assert(status && dir && filename);

    gru_config_t *ret = (gru_config_t *) calloc(1, sizeof(gru_config_t));
    
    if (ret == NULL) {
        gru_status_set(status, GRU_FAILURE, 
                       "Unable to allocate memory for gru config");
        
        return NULL;
    }
    
    asprintf(&ret->dir, "%s", dir);
    asprintf(&ret->filename, "%s", filename);
    ret->payload = payload;
    
    // open file
    ret->file = gru_io_open_file(ret->dir, ret->filename, status);
    if (!ret->file) {
        free(ret->dir);
        free(ret->filename);
        free(ret);
        
        return NULL;
    }

    return ret;
}

void gru_config_destroy(gru_config_t **config) {
    fclose((*config)->file);
    
    free((*config)->dir);
    free((*config)->filename);
    free(*config);
    *config = NULL;
}

void gru_config_set(char *dest, uint32_t size, const char *fmt, ...)
{
    va_list ap;
    pthread_mutex_t mutex;

    pthread_mutex_lock(&mutex);
    va_start(ap, fmt);

    vsnprintf(dest, size, fmt, ap);

    va_end(ap);
    pthread_mutex_unlock(&mutex);
}

void gru_config_read(void *dest, FILE *source, const char *mask, const char *name)
{
    pthread_mutex_t mutex;
    pthread_mutex_lock(&mutex);

    rewind(source);
    while (!feof(source)) {
        char line[GRU_OPT_MAX_STR_SIZE];

        bzero(line, GRU_OPT_MAX_STR_SIZE);
        fgets(line, GRU_OPT_MAX_STR_SIZE - 1, source);

        gru_trim(line, sizeof (line));

        if (strstr(line, name) != NULL) {
            char none[GRU_OPT_MAX_STR_SIZE];

            bzero(none, sizeof (none));
            sscanf(line, mask, none, dest);

            goto end;
        }
    }

end:
    pthread_mutex_unlock(&mutex);
}

void gru_config_init_payload(gru_config_t *config, gru_payload_t *payload, 
                             gru_status_t *status)
{
    if (!gru_path_exists(config->filename, status) && status->code == GRU_SUCCESS) {
        // set defaults
        payload->init(payload->data);

        // write configs
        payload->save(config->file, payload->data);
        
        fflush(NULL);
    }
    else {
        if (status->code != GRU_SUCCESS) {
            return;
        }
        
        payload->data = payload->read(config->file);
    }   
}

void gru_config_read_char(char *dest, FILE *source, const char *name)
{
    gru_config_read(dest, source, "%[^=]=" GRU_OPT_MAX_STR_SIZE_MASK, name);

}

void gru_config_read_int(int32_t *dest, FILE *source, const char *name)
{
    gru_config_read(dest, source, "%[^=]=%"PRId32"", name);
}

void gru_config_read_short(int16_t *dest, FILE *source, const char *name)
{
    gru_config_read(dest, source, "%[^=]=%h"PRIi16, name);
}

void gru_config_write_int(FILE *dest, const char *name, int32_t value)
{
    fprintf(dest, "%s=%h"PRId32"\n", name, value);
}

void gru_config_write_short(FILE *dest, const char *name, int16_t value)
{
    fprintf(dest, "%s=%h"PRIi16"\n", name, value);
}

void gru_config_write_string(FILE *dest, const char *name, const char *value)
{
    fprintf(dest, "%s=%s\n", name, value);
}



