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
#ifndef GRU_NODE_INFO_H
#define GRU_NODE_INFO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Node information container
 */
typedef struct gru_node_info_t_ {
	uint32_t parent_pos; /* Parent node position */
	uint32_t self_pos; /* Self position */
} gru_node_info_t;

#ifdef __cplusplus
}
#endif

#endif /* GRU_NODE_INFO_H */
