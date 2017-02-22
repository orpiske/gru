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
#ifndef GRU_COLLECTION_CALLBACKS_H
#define GRU_COLLECTION_CALLBACKS_H

#include <stdbool.h>

#include "gru_node_info.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Comparator function for the collections module
 */
typedef bool (*compare_function_t)(const void *, const void *data, void *result);

/**
 * Handler function for the collections module
 */
typedef void (*handle_function_t)(const void *, void *);

/**
 * A handler function for the collections module that also receiver node information
 */
typedef void (*handle_function_info_t)(const void *, gru_node_info_t info, void *);

typedef handle_function_t tree_callback_fn;

#ifdef __cplusplus
}
#endif

#endif /* GRU_COLLECTION_CALLBACKS_H */
