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
#ifndef GRU_TREE_H
#define GRU_TREE_H

#include "gru_node.h"
#include "gru_list.h"

#ifdef __cplusplus
extern "C" {
#endif
    
typedef struct gru_tree_node_t_ {
    gru_tree_node_t *parent;
    gru_list_t *children;
    const void *data ;
} gru_tree_node_t;

gru_tree_node_t gru_tree_node_new(const void *data);
void gru_tree_node_destroy(gru_tree_node_t **ptr);

gru_tree_node_t *gru_tree_node_add_child(gru_tree_node_t *node, const void *data);
void gru_tree_node_remove_child(gru_tree_node_t *node, 
                                compare_function_t comparable, 
                                const void *other);


#ifdef __cplusplus
}
#endif

#endif /* GRU_TREE_H */

