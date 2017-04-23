/*
 Copyright 2017 Otavio Rodolfo Piske

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
#ifndef GRU_LOCALTIME_H_
#define GRU_LOCALTIME_H_

#include <time.h>

#if !defined(_WIN32) && !defined(_WIN64)
#include <sys/time.h>
#include <unistd.h>
#else
#include <windows.h>
#endif

#include <common/gru_status.h>

gru_export bool gru_localtime(const time_t *timep, struct tm *result, gru_status_t *status);

#endif // GRU_LOCALTIME_H_