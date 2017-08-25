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
#include "gru_path.h"
#include "common/gru_alloc.h"

bool gru_path_exists(const char *filename, gru_status_t *status) {
	int ret = 0;
	struct stat info;

	ret = stat(filename, &info);
	if (ret == 0) {
		return true;
	}

	if (errno == ENOENT) {
		return false;
	}

	if (status) {
		gru_status_strerror(status, GRU_FAILURE, errno);
	}

	return false;
}

bool gru_path_fexists(int fd, gru_status_t *status) {
	int ret = 0;
	struct stat info;

	ret = fstat(fd, &info);
	if (ret == 0) {
		return true;
	}

	if (errno == ENOENT) {
		return false;
	}

	if (status) {
		gru_status_strerror(status, GRU_FAILURE, errno);
	}

	return false;
}

bool gru_path_can_read_write(const char *filename, gru_status_t *status) {
	int ret = 0;

	ret = access(filename, R_OK | W_OK);
	if (ret < 0) {
		switch (errno) {
			case ENOENT: {
				gru_status_set(status,
					GRU_FAILURE,
					"No such file or directory %s: %s",
					filename,
					strerror(errno));

				return false;
			}
			case EACCES: {
				gru_status_set(status,
					GRU_FAILURE,
					"Access denied (no read/write permission) %s: %s",
					filename,
					strerror(errno));
				return false;
			}
			default: {
				gru_status_strerror(status, GRU_FAILURE, errno);
				return false;
			}
		}
	}

	return true;
}

bool gru_path_rename_cond(const char *filename,
	gru_path_cond_t cond,
	gru_status_t *status) {

	// Return if the condition is already fulfilled
	if (!cond(filename, status)) {
		return true;
	}

	if (!gru_path_can_read_write(filename, status)) {
		return false;
	}

	char *new_file = NULL;

	int i = 0;
	do {

		if (asprintf(&new_file, "%s.%03i", filename, i) == -1) {
			gru_status_set(status, GRU_FAILURE, "Not enough memory to create a new filename");

			return false;
		}

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
	} while (true);

	free(new_file);
	return true;
}

bool gru_path_rename(const char *filename, gru_status_t *status) {
	return gru_path_rename_cond(filename, gru_path_exists, status);
}

char *gru_path_format(const char *dir, const char *name, gru_status_t *status) {
	char *ret = NULL;
	
	if (asprintf(&ret, "%s/%s", dir, name) == -1) {
		gru_status_set(status, GRU_FAILURE, "Not enough memory to format the path");

		return NULL;
	}

	return ret;
}

bool gru_path_mkdir(const char *path, gru_status_t *status) {
	int ret = 0;

	ret = mkdir(path, 0774);
	if (ret != 0) {

		gru_status_strerror(status, GRU_FAILURE, errno);
		return false;
	}

	return true;
}

bool gru_path_mkdirs(const char *path, gru_status_t *status) {
	const char *ptr = path;
	int count = 0;
	size_t tmp_size = strlen(path) + 1;
	char *tmp = gru_alloc(tmp_size, status);
	gru_alloc_check(tmp, false);

	do {
		const char *last = ptr;

		ptr++;
		ptr = strstr(ptr, FILE_SEPARATOR);
		count += (int) (ptr - last);

		snprintf(tmp, tmp_size, "%.*s", count, path);

		if (gru_path_exists(tmp, status)) {
			continue;
		}

		if (!gru_path_mkdir(tmp, status)) {
			free(tmp);

			return false;
		}
	} while (ptr != NULL);

	free(tmp);
	return true;
}
