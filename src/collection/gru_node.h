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

#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>

#include "common/gru_portable.h"

typedef struct gru_node_t_ {
	struct gru_node_t_ *next;
	struct gru_node_t_ *previous;
	const void *data;
} gru_node_t;

/**
 * Creates a new node
 * @param ptr data pointer
 * @return a new node
 */
gru_export gru_node_t *gru_node_new(const void *ptr);

/**
 * Destroys a node and sets is address to NULL
 * @param node a pointer to the node pointer to destroy
 */
gru_export void gru_node_destroy(gru_node_t **node);

/**
 * Sets the previous node for a given node
 * @param node the node to set
 * @param previous the node to be set as a previous to the node
 */
gru_export void gru_node_set_previous(gru_node_t *gru_restrict node,
	gru_node_t *gru_restrict previous);

/**
 * Sets the next node for a given node
 * @param node the node to set
 * @param next the node to be set as the next to the node
 */
gru_export void gru_node_set_next(gru_node_t *gru_restrict node,
	gru_node_t *gru_restrict next);

/**
 * Reset the pointers for the node and unassign the next and previous pointers
 * @param node the node to reset
 */
gru_export void gru_node_reset(gru_node_t *gru_restrict node);

/**
 * Unlink a node from it's previous and next node and resets it
 * @param node the node to unlink
 */
gru_export void gru_node_unlink(gru_node_t *gru_restrict node);

#define gru_node_get_data_ptr(type, node) (type *) (node)->data
#define gru_node_get_data(type, node) (*(gru_node_get_data_ptr(type, node)))

#endif
