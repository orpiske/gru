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

typedef enum gru_uri_parse_opt_t_ {
	GRU_URI_PARSE_DEFAULT = 0,
	GRU_URI_PARSE_STRIP = 1,
} gru_uri_parse_opt_t;

typedef enum gru_uri_format_opt_t_ {
	GRU_URI_FORMAT_NONE = 0, /** Formats only scheme and host */
	GRU_URI_FORMAT_PORT = 1, /** Formats only scheme, host and port if available*/
	GRU_URI_FORMAT_PATH = 2, /** Formats scheme, host, port and path if available */
	GRU_URI_FORMAT_DEFAULT =
		GRU_URI_FORMAT_PORT | GRU_URI_FORMAT_PATH, /** Default (everything) */
} gru_uri_format_opt_t;

typedef struct gru_uri_t_ {
	char *scheme;
	char *host;
	char *path;
	uint16_t port;
} gru_uri_t;

gru_export gru_uri_t gru_uri_parse(
	const char *gru_restrict uri, gru_status_t *gru_restrict status);
gru_export gru_uri_t gru_uri_parse_ex(const char *gru_restrict url,
	gru_uri_parse_opt_t parseopt, gru_status_t *gru_restrict status);

gru_export char *gru_uri_simple_format(
	gru_uri_t *gru_restrict uri, gru_status_t *gru_restrict status);

gru_export char *gru_uri_format(gru_uri_t *gru_restrict uri, gru_uri_format_opt_t fopt,
	gru_status_t *gru_restrict status);

gru_export bool gru_uri_set_scheme(gru_uri_t *uri, const char *scheme);
gru_export bool gru_uri_set_path(gru_uri_t *uri, const char *path);

gru_export gru_uri_t gru_uri_clone(gru_uri_t other, gru_status_t *status);

gru_export void gru_uri_cleanup(gru_uri_t *uri);

#ifdef __cplusplus
}
#endif

#endif /* GRU_URI_H */
