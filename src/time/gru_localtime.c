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
#include "gru_localtime.h"

bool gru_localtime(const time_t *timep, struct tm *result, gru_status_t *status) { 
    #if !defined(_WIN32) && !defined(_WIN64)
        struct tm *creation_tm = localtime_r(timep, result);

        if (!creation_tm) {
            gru_status_set(status, GRU_FAILURE, "Unable to obtain local time from the given input");
            
            return false;
        }
    #else
        if (localtime_s(result, timep) != 0) {
            gru_status_set(status, GRU_FAILURE, "Unable to obtain local time from the given input");
            
            return false;
        }
    #endif

    return true;
}