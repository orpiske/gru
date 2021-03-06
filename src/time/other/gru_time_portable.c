/*
 * Copyright 2017 Otavio Piske <angusyoung@gmail.com>.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "gru_time_portable.h"

#if (!defined __linux__ && !defined __APPLE__)
/*
 * Timer subtraction, highly inspired on the code shown at:
 * http://www.gnu.org/software/libc/manual/html_node/Elapsed-Time.html
 */

int gru_time_timersub(struct timeval *start,
	struct timeval *end,
	struct timeval *result) {
	if (start->tv_usec < end->tv_usec) {
		int nsec = (end->tv_usec - start->tv_usec) / 1000000 + 1;
		end->tv_usec -= 1000000 * nsec;
		end->tv_sec += nsec;
	}
	if (start->tv_usec - end->tv_usec > 1000000) {
		int nsec = (start->tv_usec - end->tv_usec) / 1000000;
		end->tv_usec += 1000000 * nsec;
		end->tv_sec -= nsec;
	}

	result->tv_sec = start->tv_sec - end->tv_sec;
	result->tv_usec = start->tv_usec - end->tv_usec;

	return start->tv_sec < end->tv_sec;
}
#endif
