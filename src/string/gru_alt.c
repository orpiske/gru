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
#include "gru_alt.h"

#ifndef HAVE_STRLCPY
size_t strlcpy(char *dst, const char *src, size_t len) {
	size_t size = 0;

	if (len == 0 || unlikely(dst == NULL) || unlikely(src == NULL)) {
		return 0;
	}

	size = strlen(src);
	if (size >= len) {
		size = len - 1;
	}

	memcpy(dst, src, size);
	dst[size] = 0;

	return size;
}
#endif