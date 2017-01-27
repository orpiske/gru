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

/**
 * Portable, non-Linux, time utilities
 */

#ifndef GRU_TIME_PORTABLE_H
#define GRU_TIME_PORTABLE_H

#if !defined(_WIN32) && !defined(_WIN64)
#include <sys/time.h>
#else
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !defined __linux__ && !defined timersub
int gru_time_timersub(struct timeval *start, struct timeval *end, struct timeval *result);

#define timersub(start, end, result) gru_time_timersub(start, end, result)
#endif

#ifdef __cplusplus
}
#endif

#endif /* GRU_TIME_PORTABLE_H */
