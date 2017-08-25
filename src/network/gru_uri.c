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

#include "gru_uri.h"

static inline size_t gru_uri_calc_buffer_size(UriTextRangeA *range) {
	if (!range || !range->first) {
		return 0;
	}

	if (range->afterLast) {
		return range->afterLast - range->first;
	}

	return strlen(range->first);

}

static char *gru_uri_get_ranged_data(UriTextRangeA *range, gru_status_t *status) {
	if (!range->first || !range->afterLast) {
		return NULL;
	}

	size_t len = gru_uri_calc_buffer_size(range);

	size_t buff_size = len + 1;
	char *ret = gru_alloc(buff_size, status);
	gru_alloc_check(ret, NULL);

	strlcpy(ret, range->first, buff_size);

	return ret;
}

static uint16_t gru_uri_get_port(UriTextRangeA *range, gru_status_t *status) {
	uint16_t ret = 0;

	const char *port = gru_uri_get_ranged_data(range, status);

	if (!port) {
		return 0;
	}

	if (gru_status_error(status)) {
		gru_dealloc_const_string(&port);

		return 0;
	}

	ret = (uint16_t) atoi(port);
	gru_dealloc_const_string(&port);

	return ret;
}

/**
 * Calculate the required buffer size for storing the whole path taking into account the
 * path separator
 * @param uri
 * @return
 */
static size_t gru_uri_calc_path_size(UriUriA *uri) {
	size_t total = 1; // starts /w 1 for the initial /
	UriPathSegmentA *cur = uri->pathHead;

	while (cur) {
		// Adds + 1 for the '/' path separator
		total += gru_uri_calc_buffer_size(&cur->text) + 1;

		cur = cur->next;
	}

	return total;
}

static char *gru_uri_path(UriUriA *gru_restrict uri,
	gru_uri_parse_opt_t parseopt,
	gru_status_t *gru_restrict status) {
	size_t total = gru_uri_calc_path_size(uri);

	char *ret = gru_alloc(total, status);
	gru_alloc_check(ret, NULL);

	UriPathSegmentA *cur = uri->pathHead;
	while (cur) {
		const char *cur_path = gru_uri_get_ranged_data(&cur->text, status);
		if (!cur_path) {
			gru_dealloc_string(&ret);

			return NULL;
		}

		if (gru_status_error(status)) {
			gru_dealloc_string(&ret);
			gru_dealloc_const_string(&cur_path);

			return NULL;
		}

		if (!(parseopt & GRU_URI_PARSE_STRIP)) {
			strlcat(ret, "/", total);
		}

		strlcat(ret, cur_path, total);

		gru_dealloc_const_string(&cur_path);

		if (!(parseopt & GRU_URI_PARSE_STRIP)) {
			cur = cur->next;
		} else {
			break;
		}
	}

	return ret;
}

gru_uri_t gru_uri_parse(const char *url, gru_status_t *status) {
	return gru_uri_parse_ex(url, GRU_URI_PARSE_DEFAULT, status);
}

static gru_list_t *gru_uri_parse_query(UriUriA *uri, gru_status_t *status) {
	UriQueryListA *query_list;
	int items = 0;

	if (uri->query.first == 0 && uri->query.afterLast == 0) {
		return NULL;
	}

	if (uriDissectQueryMallocA(&query_list, &items, uri->query.first, uri->query.afterLast) != URI_SUCCESS) {
		uriFreeUriMembersA(uri);
		gru_status_set(status, GRU_FAILURE, "Unable to parse query string from URL");

		return false;
	}

	if (items == 0) {
		return NULL;
	}

	gru_list_t *ret = gru_list_new(status);
	gru_alloc_check(ret, NULL);

	struct UriQueryListStructA *ptr = query_list;
	for (int i = 0; i < items; i++) {

		gru_keypair_t *kp = gru_keypair_new(status);
		if (!kp) {
			uriFreeQueryListA(query_list);

			gru_list_clean(ret, gru_keypair_destroy_list_item);

			gru_list_destroy(&ret);
			return NULL;
		}

		gru_keypair_set_key(kp, ptr->key);

		*kp->pair = gru_variant_parse(ptr->value);

		gru_list_append(ret, kp);

		ptr = ptr->next;
	}

	uriFreeQueryListA(query_list);
	return ret;
}

gru_export gru_uri_t gru_uri_parse_ex(const char *gru_restrict url,
	gru_uri_parse_opt_t parseopt,
	gru_status_t *gru_restrict status) {
	gru_uri_t ret = {0};
	UriParserStateA state;
	UriUriA uri;

	state.uri = &uri;
	if (uriParseUriA(&state, url) != URI_SUCCESS) {
		uriFreeUriMembersA(&uri);
		gru_status_set(status, GRU_FAILURE, "Unable to parse URL %s", url);

		return ret;
	}

	ret.host = gru_uri_get_ranged_data(&uri.hostText, status);
	ret.port = gru_uri_get_port(&uri.portText, status);
	ret.path = gru_uri_path(&uri, parseopt, status);
	ret.scheme = gru_uri_get_ranged_data(&uri.scheme, status);

	ret.query = gru_uri_parse_query(&uri, status);
	if (!gru_status_success(status)) {
		uriFreeUriMembersA(&uri);

		return ret;
	}

	uriFreeUriMembersA(&uri);

	return ret;
}

char *gru_uri_simple_format(const gru_uri_t *uri, gru_status_t *status) {
	char *ret = {0};
	int rc = 0;

	if (uri->port != 0) {
		if (uri->path) {
			rc = asprintf(&ret,
				"%s://%s:%" PRIu16 "%s",
				uri->scheme,
				uri->host,
				uri->port,
				uri->path);
		} else {
			rc = asprintf(&ret, "%s://%s:%" PRIu16 "", uri->scheme, uri->host, uri->port);
		}
	} else {
		if (uri->path) {
			rc = asprintf(&ret, "%s://%s%s", uri->scheme, uri->host, uri->path);
		} else {
			rc = asprintf(&ret, "%s://%s", uri->scheme, uri->host);
		}
	}

	if (rc == -1) {
		gru_status_set(status, GRU_FAILURE, "Not enough memory to format the URI");

		return NULL;
	}

	return ret;
}

char *gru_uri_format(const gru_uri_t *uri,
	gru_uri_format_opt_t fopt,
	gru_status_t *status) {
	char *ret = {0};
	int rc = 0;

	if (uri->port != 0 && (fopt & GRU_URI_FORMAT_PORT)) {
		if (uri->path && (fopt & GRU_URI_FORMAT_PATH)) {
			rc = asprintf(&ret,
				"%s://%s:%" PRIu16 "%s",
				uri->scheme,
				uri->host,
				uri->port,
				uri->path);
		} else {
			rc = asprintf(&ret, "%s://%s:%" PRIu16 "", uri->scheme, uri->host, uri->port);
		}
	} else {
		if (uri->path && (fopt & GRU_URI_FORMAT_PATH)) {
			rc = asprintf(&ret, "%s://%s%s", uri->scheme, uri->host, uri->path);
		} else {
			rc = asprintf(&ret, "%s://%s", uri->scheme, uri->host);
		}
	}

	if (rc == -1) {
		gru_status_set(status, GRU_FAILURE, "Not enough memory to format the URI");

		return NULL;
	}

	return ret;
}

bool gru_uri_set_scheme(gru_uri_t *uri, const char *scheme) {
	gru_dealloc_string(&uri->scheme);

	if (asprintf(&uri->scheme, "%s", scheme) == -1) {
		return false;
	}

	return true;
}

bool gru_uri_set_path(gru_uri_t *uri, const char *path) {
	gru_dealloc_string(&uri->path);

	if (path) {
		if (asprintf(&uri->path, "%s", path) == -1) {
			return false;
		}
	} else {
		uri->path = NULL;
	}

	return true;
}

gru_export gru_uri_t gru_uri_clone(gru_uri_t other, gru_status_t *status) {
	gru_uri_t ret = {0};

	if (other.host) {
		ret.host = strdup(other.host);
		if (!ret.host) {
			goto err_exit;
		}
	}

	if (other.path) {
		ret.path = strdup(other.path);

		if (!ret.path) {
			goto err_exit;
		}
	}

	ret.port = other.port;

	if (other.scheme) {
		ret.scheme = strdup(other.scheme);
		if (!ret.scheme) {
			goto err_exit;
		}
	}

	if (other.query) {
		ret.query = gru_list_new(status);


		gru_node_t *node = other.query->root;

		while (node) {
			gru_keypair_t *kp = (gru_keypair_t *) node->data;
			gru_keypair_t *clone = gru_keypair_clone(kp, status);

			if (!gru_list_append(ret.query, clone)) {
				goto err_exit;
			}

			node = node->next;
		}
	}

	return ret;

err_exit:
	gru_uri_cleanup(&ret);
	gru_status_set(status, GRU_FAILURE, "Not enough memory");
	return ret;
}

void gru_uri_cleanup(gru_uri_t *uri) {
	if (!uri) {
		return;
	}

	gru_dealloc_string(&uri->host);
	gru_dealloc_string(&uri->path);
	gru_dealloc_string(&uri->scheme);

	if (uri->query) {
		gru_list_clean(uri->query, gru_keypair_destroy_list_item);

		gru_list_destroy(&uri->query);
	}
}
