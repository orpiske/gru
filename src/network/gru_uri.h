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
#ifndef GRU_URI_H
#define GRU_URI_H

#include <inttypes.h>
#include <stdbool.h>

#include <common/gru_status.h>
#include <string/gru_alt.h>

#include <uriparser/Uri.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct gru_uri_t_ {
    char *scheme;
    char *host;
    uint16_t port;
    char *path;
} gru_uri_t;

gru_uri_t gru_uri_parse(const char * gru_restrict uri, gru_status_t * gru_restrict status);
char *gru_uri_simple_format(gru_uri_t * gru_restrict uri, gru_status_t * gru_restrict status);

bool gru_uri_set_scheme(gru_uri_t *uri, const char *scheme);
bool gru_uri_set_path(gru_uri_t *uri, const char *path);

void gru_uri_cleanup(gru_uri_t *uri);



#ifdef __cplusplus
}
#endif

#endif /* GRU_URI_H */

