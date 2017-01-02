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
#include "common/gru_alloc.h"

bool gru_io_remap(const char *dir, const char *name, FILE *fd, gru_status_t *status) {
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

static FILE *gru_io_open_file_path_int(
	const char *path, const char *mode, gru_status_t *status) {
	FILE *f = fopen(path, mode);
	if (f == NULL) {
		gru_status_t lc_status = {0};
		gru_status_strerror(&lc_status, GRU_FAILURE, errno);
		gru_status_set(status, GRU_FAILURE, "%s: %s", lc_status.message, path);

		gru_status_reset(&lc_status);
		return NULL;
	}

	return f;
}

FILE *gru_io_open_file_path(const char *path, gru_status_t *status) {
	return gru_io_open_file_path_int(path, "w+", status);
}

FILE *gru_io_open_file(const char *dir, const char *name, gru_status_t *status) {

	char *fullpath = gru_path_format(dir, name, status);

	if (!gru_path_exists(fullpath, status) && (status->code == GRU_SUCCESS)) {
		if (!gru_path_mkdirs(dir, status)) {

			gru_dealloc_string(&fullpath);
			return NULL;
		}
	}

	FILE *f = gru_io_open_file_path(fullpath, status);

	gru_dealloc_string(&fullpath);
	return f;
}

FILE *gru_io_open_file_read(const char *dir, const char *name, gru_status_t *status) {

	char *fullpath = gru_path_format(dir, name, status);

	if (!gru_path_exists(fullpath, status) && (status->code == GRU_SUCCESS)) {
		if (!gru_path_mkdirs(dir, status)) {

			gru_dealloc_string(&fullpath);
			return NULL;
		}
	}

	FILE *f = gru_io_open_file_path_int(fullpath, "r+", status);

	gru_dealloc_string(&fullpath);
	return f;
}

FILE *gru_io_open_file_read_path(const char *path, gru_status_t *status) {
	return gru_io_open_file_path_int(path, "r+", status);
}

FILE *gru_io_open_unique_file(const char *dir, const char *name, gru_status_t *status) {

	char *fullpath = gru_path_format(dir, name, status);

	if (!gru_path_rename(fullpath, status)) {
		free(fullpath);
		return NULL;
	}

	FILE *f = gru_io_open_file_path_int(fullpath, "w+", status);

	free(fullpath);
	return f;
}

size_t gru_io_read_text_into(char **dest, FILE *file, gru_status_t *status) {
	fseek(file, 0L, SEEK_END);

	long size = ftell(file);
	if (size == -1) {
		gru_status_strerror(status, GRU_FAILURE, errno);

		return 0;
	}

	rewind(file);

	char *ret = gru_alloc((size_t) size + 1, status);
	gru_alloc_check(ret, 0);

	long cur = 0;
	while (true) {
		int c = fgetc(file);

		if (c != EOF && cur <= size) {
			ret[cur] = (char) c;
			cur++;
		} else {
			break;
		}
	}

	if (cur != size) {
		gru_status_strerror(status, GRU_FAILURE, errno);
		gru_dealloc_string(&ret);

		return 0;
	}

	*dest = ret;
	return (size_t) size;
}