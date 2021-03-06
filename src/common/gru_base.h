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
#ifndef GRU_BASE_H
#define GRU_BASE_H

#include <stdio.h>
#include <stdlib.h>

#if !defined(_WIN32) && !defined(_WIN64)
#include <pwd.h>
#include <unistd.h>
#endif
#include <sys/types.h>

#include "gru_portable.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GRU_OPT_MAX_STR_SIZE 256
#define GRU_OPT_MAX_STR_SIZE_MASK "%256s"
#define GRU_OPT_MAX_CHAR_SIZE_MASK "%256c"

/**
 * Returns the base directory for the application given an application name
 * For Unix-like, that would be: $HOME/.appname
 * @param appname Application name
 * @return a pointer to a static buffer that will be automatically free'd at exit
 */
gru_export const char *gru_base_app_home(const char *appname);

#ifdef __cplusplus
}
#endif

#endif /* GRU_BASE_H */
