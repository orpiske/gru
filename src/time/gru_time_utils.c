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
#include "gru_time_utils.h"

void gru_time_add_microseconds(gru_timestamp_t *t, uint64_t count) {
	t->tv_usec = t->tv_usec + count;

	while (t->tv_usec >= 1000000) {
		t->tv_sec++;
		t->tv_usec -= 1000000;
	}
}

void gru_time_add_seconds(gru_timestamp_t *t, uint64_t count) {
	t->tv_sec = t->tv_sec + count;
}

void gru_time_add_minutes(gru_timestamp_t *t, uint64_t count) {
	gru_time_add_seconds(t, (count * 60));
}

void gru_time_add_hours(gru_timestamp_t *t, uint64_t count) {
	gru_time_add_minutes(t, (count * 60));
}

void gru_time_add_days(gru_timestamp_t *t, uint64_t count) {
	gru_time_add_hours(t, (count * 24));
}

gru_timestamp_t gru_time_read_str(const char *str) {
	gru_timestamp_t ret = {0};
	int pos = 0;

	// This, I hope, should be sufficient for years to come ...
	char sec[GRU_TS_STRING_SEC_MAX] = {0};

	// 999999
	char usec[GRU_TS_STRING_USEC_MAX] = {0};

	while (pos < sizeof(sec) && isdigit(str[pos])) {
		sec[pos] = str[pos];
		pos++;
	}

	pos++;
	int usecl = 0;
	while (usecl < (sizeof(usec) - 1) && isdigit(str[pos])) {
		usec[usecl] = str[pos];
		pos++;
		usecl++;
	}

	ret.tv_sec = atol(sec);
	ret.tv_usec = atol(usec);

	return ret;
}

char *gru_time_write_str(const gru_timestamp_t *t) {
	char *ret = NULL;
#if defined(__arm__) && !defined(_LP64)
	if (asprintf(&ret, "%" PRIu32 ".%" PRIu32 "", t->tv_sec, t->tv_usec) == -1) {
		return NULL;
	}
#else
	if (asprintf(&ret, "%" PRIu64 ".%" PRIu64 "", t->tv_sec, t->tv_usec) == -1) {
		return NULL;
	}
#endif // __arm__

	return ret;
}

char *gru_time_write_format(const gru_timestamp_t *t,
	const char *format,
	gru_status_t *status) {
	char tmp_buff[64] = {0};

	struct tm result;

	if (!gru_localtime(&t->tv_sec, &result, status)) {
		return NULL;
	}

	strftime(tmp_buff, sizeof(tmp_buff), format, &result);
	char *ret = strdup(tmp_buff);
	if (!ret) {
		gru_status_strerror(status, GRU_FAILURE, errno);
	}

	return ret;
}

gru_timestamp_t gru_time_now() {
	gru_timestamp_t ret = {.tv_sec = 0, .tv_usec = 0};

	gettimeofday(&ret, NULL);
	return ret;
}

uint64_t gru_time_now_milli() {
	gru_timestamp_t now = gru_time_now();

	return gru_time_to_milli(&now);
}

gru_timestamp_t gru_time_from_milli(int64_t timestamp) {

	gru_timestamp_t ret = {0};

	double ts = ((double) timestamp / 1000);
	double integral;

	ret.tv_usec = modf(ts, &integral) * 1000000;
	ret.tv_sec = integral;

	return ret;
}

gru_timestamp_t gru_time_from_milli_char(const char *ts) {
	uint64_t ms = strtoull(ts, NULL, 10);

	return gru_time_from_milli(ms);
}

uint64_t gru_time_to_milli(const gru_timestamp_t *ts) {
	uint64_t ret = ((uint64_t) ts->tv_sec * 1000) + ((uint64_t) ts->tv_usec / 1000);

	return ret;
}


uint64_t gru_time_elapsed_secs(gru_timestamp_t start, gru_timestamp_t end) {
	gru_timestamp_t ret = {.tv_sec = 0, .tv_usec = 0};

	timersub(&end, &start, &ret);

	return ret.tv_sec;
}

uint64_t gru_time_elapsed_milli(gru_timestamp_t start, gru_timestamp_t end) {
	gru_timestamp_t ret = {.tv_sec = 0, .tv_usec = 0};

	timersub(&end, &start, &ret);

	return gru_time_to_milli(&ret);
}