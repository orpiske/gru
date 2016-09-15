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

#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>


typedef struct gru_node_t_ {
	struct gru_node_t_ *next;
	struct gru_node_t_ *previous;
	const void *data;
} gru_node_t;

typedef struct gru_node_t_ gru_node_t;

gru_node_t *gru_node_new(const void *ptr);
void gru_node_destroy(gru_node_t **node);

void gru_node_set_previous(gru_node_t *node, gru_node_t *previous);
void gru_node_set_next(gru_node_t *node, gru_node_t *next);
void gru_node_reset(gru_node_t *node);
void gru_node_unlink(gru_node_t *node);

#endif
