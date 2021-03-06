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
#include "gru_duration.h"

gru_duration_t gru_duration_new() {
	gru_duration_t duration = {0};

	gettimeofday(&duration.start, NULL);
	duration.end = duration.start;

	return duration;
}

gru_duration_t gru_duration_from_seconds(uint64_t seconds) {
	gru_duration_t duration = {0};

	gettimeofday(&duration.start, NULL);
	duration.end = duration.start;

	gru_time_add_seconds(&duration.end, seconds);

	return duration;
}

gru_duration_t gru_duration_from_minutes(uint64_t minutes) {
	gru_duration_t duration = {0};

	gettimeofday(&duration.start, NULL);
	duration.end = duration.start;

	gru_time_add_minutes(&duration.end, minutes);

	return duration;
}

uint64_t gru_duration_seconds(gru_duration_t duration) {
	return duration.end.tv_sec - duration.start.tv_sec;
}

uint64_t gru_duration_minutes(gru_duration_t duration, double *fractional) {
	// Gets the number of seconds
	uint64_t seconds = gru_duration_seconds(duration);

	// Convert the amount of seconds to minutes
	double mint = ((double) seconds / 60);
	double integral;
	double discard;

	// From minutes, get the integral part. If fractional pointer is given,
	// set its value, otherwise discard it
	discard = modf(mint, &integral);
	if (fractional) {
		*fractional = discard;
	}

	return (uint64_t) integral;
}


bool gru_duration_parse(gru_duration_t *duration, const char *str) {
	if (!duration || !str) {
		return false;
	}

	char tmp[64] = {0};
	size_t len = strlen(str);

	if (len > sizeof(tmp)) {
		return false;
	}

	int16_t r = 0;
	for (size_t i = 0; i < len; i++) {
		if (str[i] == 's') {
			if (strlen(tmp) == 0) {
				return false;
			}

			gru_time_add_seconds(&duration->end, atol(tmp));
			bzero(&tmp, sizeof(tmp));
			r = 0;
		} else if (str[i] == 'm') {
			if (strlen(tmp) == 0) {
				return false;
			}

			gru_time_add_minutes(&duration->end, atol(tmp));
			bzero(&tmp, sizeof(tmp));
			r = 0;
		} else if (str[i] == 'h') {
			if (strlen(tmp) == 0) {
				return false;
			}

			gru_time_add_hours(&duration->end, atol(tmp));
			bzero(&tmp, sizeof(tmp));
			r = 0;
		} else if (str[i] == 'd') {
			if (strlen(tmp) == 0) {
				return false;
			}

			gru_time_add_days(&duration->end, atol(tmp));
			bzero(&tmp, sizeof(tmp));
			r = 0;
		} else {
			tmp[r] = str[i];
			r++;
			if (i == (len - 1)) {
				return false;
			}
		}
	}

	return true;
}