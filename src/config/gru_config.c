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

void gru_config_read(const char *name, FILE *source, void *dest, const char *mask)
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

void gru_config_read_string(const char *name, FILE *source, char *dest)
{
    gru_config_read(name, source, dest, "%[^=]=" GRU_OPT_MAX_CHAR_SIZE_MASK);

}

void gru_config_read_short(const char *name, FILE *source, int16_t *dest)
{
    gru_config_read(name, source, dest, "%[^=]=%h"PRId16);
}

void gru_config_read_ushort(const char *name, FILE *source, uint16_t *dest)
{
    gru_config_read(name, source, dest, "%[^=]=%h"PRIu16);
}

void gru_config_read_int(const char *name, FILE *source, int32_t *dest)
{
    gru_config_read(name, source, dest, "%[^=]=%"PRId32"");
}

void gru_config_read_uint(const char *name, FILE *source, uint32_t *dest)
{
    gru_config_read(name, source, dest, "%[^=]=%"PRIu32"");
}

void gru_config_read_long(const char *name, FILE *source, int64_t *dest)
{
    gru_config_read(name, source, dest, "%[^=]=%"PRId64"");
}

void gru_config_read_ulong(const char *name, FILE *source, uint64_t *dest)
{
    gru_config_read(name, source, dest, "%[^=]=%"PRIu64"");
}

void gru_config_write_short(const char *name, FILE *dest, int16_t value)
{
    fprintf(dest, "%s=%h"PRIi16"\n", name, value);
}

void gru_config_write_ushort(const char *name, FILE *dest, uint16_t value)
{
    fprintf(dest, "%s=%h"PRIu16"\n", name, value);
}

void gru_config_write_int(const char *name, FILE *dest, int32_t value)
{
    fprintf(dest, "%s=%"PRId32"\n", name, value);
}

void gru_config_write_uint(const char *name, FILE *dest, uint32_t value)
{
    fprintf(dest, "%s=%"PRIu32"\n", name, value);
}

void gru_config_write_long(const char *name, FILE *dest, int64_t value) {
    fprintf(dest, "%s=%"PRId64"\n", name, value);
}

void gru_config_write_ulong(const char *name, FILE *dest, uint64_t value) {
    fprintf(dest, "%s=%"PRIu64"\n", name, value);
}

void gru_config_write_string(const char *name, FILE *dest, const char *value)
{
    fprintf(dest, "%s=%s\n", name, value);
}



