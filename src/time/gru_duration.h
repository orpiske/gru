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
#ifndef GRU_DURATION_H
#define GRU_DURATION_H

#include <stdlib.h>

#include "gru_time_utils.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct gru_duration_t_ {
    struct timeval start;
    struct timeval end;
} gru_duration_t;


gru_duration_t gru_duration_from_seconds(uint64_t seconds);
gru_duration_t gru_duration_from_minutes(uint64_t seconds);

uint64_t gru_duration_seconds();

#ifdef __cplusplus
}
#endif

#endif /* GRU_DURATION_H */

