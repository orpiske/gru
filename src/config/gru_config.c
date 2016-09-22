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
                              gru_payload_t *payload, gru_status_t *status)
{
    assert(status && dir && filename);

    gru_config_t *ret = (gru_config_t *) calloc(1, sizeof (gru_config_t));

    if (ret == NULL) {
        gru_status_set(status, GRU_FAILURE,
                       "Unable to allocate memory for gru config");

        return NULL;
    }

    asprintf(&ret->dir, "%s", dir);
    asprintf(&ret->filename, "%s", filename);

    // open file
    /*
    ret->file = gru_io_open_file(ret->dir, ret->filename, status);
    if (!ret->file) {
        free(ret->dir);
        free(ret->filename);
        free(ret);
        
        return NULL;
    }
     */

    gru_payload_init_data(payload, ret->dir, ret->filename, &ret->file, status);

    if (status->code != GRU_SUCCESS) {
        gru_config_destroy(&ret);

        return NULL;
    }

    return ret;
}

void gru_config_destroy(gru_config_t **config)
{
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

void gru_config_read_string(char *dest, FILE *source, const char *name)
{
    gru_config_read(dest, source, "%[^=]=" GRU_OPT_MAX_CHAR_SIZE_MASK, name);

}

void gru_config_read_short(int16_t *dest, FILE *source, const char *name)
{
    gru_config_read(dest, source, "%[^=]=%h"PRId16, name);
}

void gru_config_read_ushort(uint16_t *dest, FILE *source, const char *name)
{
    gru_config_read(dest, source, "%[^=]=%h"PRIu16, name);
}

void gru_config_read_int(int32_t *dest, FILE *source, const char *name)
{
    gru_config_read(dest, source, "%[^=]=%"PRId32"", name);
}

void gru_config_read_uint(uint32_t *dest, FILE *source, const char *name)
{
    gru_config_read(dest, source, "%[^=]=%"PRIu32"", name);
}

void gru_config_read_long(int64_t *dest, FILE *source, const char *name)
{
    gru_config_read(dest, source, "%[^=]=%"PRId64"", name);
}

void gru_config_read_ulong(uint64_t *dest, FILE *source, const char *name)
{
    gru_config_read(dest, source, "%[^=]=%"PRIu64"", name);
}

void gru_config_write_short(FILE *dest, const char *name, int16_t value)
{
    fprintf(dest, "%s=%h"PRIi16"\n", name, value);
}

void gru_config_write_ushort(FILE *dest, const char *name, uint16_t value)
{
    fprintf(dest, "%s=%h"PRIu16"\n", name, value);
}

void gru_config_write_int(FILE *dest, const char *name, int32_t value)
{
    fprintf(dest, "%s=%"PRId32"\n", name, value);
}

void gru_config_write_uint(FILE *dest, const char *name, uint32_t value)
{
    fprintf(dest, "%s=%"PRIu32"\n", name, value);
}

void gru_config_write_long(FILE *dest, const char *name, int64_t value) {
    fprintf(dest, "%s=%"PRId64"\n", name, value);
}

void gru_config_write_ulong(FILE *dest, const char *name, uint64_t value) {
    fprintf(dest, "%s=%"PRIu64"\n", name, value);
}

void gru_config_write_string(FILE *dest, const char *name, const char *value)
{
    fprintf(dest, "%s=%s\n", name, value);
}



