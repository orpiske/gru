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
#include "getimeofday.h"

#if defined(_WIN32) || defined(_WIN64)
static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

/**
 * Modified version from multiple sources found on internet. See the header for
 * references
 */
int gettimeofday(struct timeval *tp, struct timezone *tzp) {
	SYSTEMTIME system_time;
	FILETIME file_time;
	uint64_t time;

	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);

	time = ((uint64_t) file_time.dwLowDateTime);
	time += ((uint64_t) file_time.dwHighDateTime) << 32;

	tp->tv_sec = (long) ((time - EPOCH) / 10000000L);
	tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
	return 0;
}
#endif