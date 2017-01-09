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
 * File:   gru_print.h
 * Author: Otavio Piske <angusyoung@gmail.com>
 *
 * Created on January 9, 2017, 5:18 PM
 */

#ifndef GRU_PRINT_H
#define GRU_PRINT_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "common/gru_colors.h"

#ifdef __cplusplus
extern "C" {
#endif

void gru_print_err(const char *msg, ...);

#ifdef __cplusplus
}
#endif

#endif /* GRU_PRINT_H */
