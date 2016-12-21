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
#ifndef GRU_TIME_UTILS_H
#define GRU_TIME_UTILS_H

#include <stdint.h>

#if !defined(_WIN32) && !defined(_WIN64)
#include <sys/time.h>
#else
#include <windows.h>
#endif

#include "common/gru_portable.h"

#ifdef __cplusplus
extern "C" {
#endif

gru_export void gru_time_add_seconds(struct timeval *t, uint64_t count);
gru_export void gru_time_add_minutes(struct timeval *t, uint64_t count);

#ifdef __cplusplus
}
#endif

#endif /* GRU_TIME_UTILS_H */
