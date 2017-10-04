/*
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

#if !defined(_WIN32) && !defined(_WIN64)
 #include <arpa/inet.h>
#else
 #include <winsock2.h>
 #include <ws2tcpip.h>
#endif

#include <common/gru_portable.h>
#include <common/gru_status.h>
#include <string/gru_alt.h>
#include <common/gru_keypair.h>
#include <common/gru_variant.h>

#include <uriparser/Uri.h>
#include <collection/gru_list.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@example config/gru_config_test.c
*/

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
  	gru_list_t *query;
} gru_uri_t;

/**
 * Default URI parser
 * @param uri URI string  (ie.: scheme://host:port/path)
 * @param status status object
 * @return A parsed URI object with each component of the URI broken down
 */
gru_export gru_uri_t gru_uri_parse(const char *gru_restrict uri,
	gru_status_t *gru_restrict status);

/**
 * URI parser with additional options
 * @param uri URI string (ie.: scheme://host:port/path)
 * @param parseopt parse options (see gru_uri_format_opt_t)
 * @param status status object
 * @return A parsed URI object with each component of the URI broken down
 */
gru_export gru_uri_t gru_uri_parse_ex(const char *gru_restrict url,
	gru_uri_parse_opt_t parseopt,
	gru_status_t *gru_restrict status);

/**
 * Converts a URI object to a string
 * @param uri a pointer to an URI object
 * @param status status object
 * @return a new URI string that must be free'd after use
 */
gru_export char *gru_uri_simple_format(const gru_uri_t *gru_restrict uri,
	gru_status_t *gru_restrict status);

/**
 * A more elaborate URI string converter that can filter parts of the URI
 * @param uri a pointer to an URI object
 * @param fopt formatting options (see gru_uri_format_opt_t)
 * @param status status object
 * @return a new URI string that must be free'd after use
 */
gru_export char *gru_uri_format(const gru_uri_t *gru_restrict uri,
	gru_uri_format_opt_t fopt,
	gru_status_t *gru_restrict status);

/**
 * Sets the scheme in a URI object
 * @param uri a pointer to an URI object
 * @param scheme the scheme to set it to
 * @return true if success or false otherwise
 */
gru_export bool gru_uri_set_scheme(gru_uri_t *uri, const char *scheme);

/**
 * Sets the URI path
 * @param uri a pointer to an URI object
 * @param path the path
 * @return true if success or false otherwise
 */
gru_export bool gru_uri_set_path(gru_uri_t *uri, const char *path);

/**
 * Clone a URI object
 * @param other the object to clone
 * @param status status object
 * @return A cloned object that must's be cleaned up after use. Check the status object
 * to determine whether cloning was successful or not
 */
gru_export gru_uri_t gru_uri_clone(gru_uri_t other, gru_status_t *status);

/**
 * Cleans up a URI object
 * @param uri a pointer to a URI object to clean
 */
gru_export void gru_uri_cleanup(gru_uri_t *uri);

#ifdef __cplusplus
}
#endif

#endif /* GRU_URI_H */
