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
#include "gru_node.h"


gru_node_t *gru_node_new(const void *ptr) {
	gru_node_t *ret = (gru_node_t *) malloc(sizeof(gru_node_t));

	if (!ret) {
		fprintf(stderr, "Not enough memory to allocate for new node\n");
	}
	ret->previous = NULL;
	ret->next = NULL;
	ret->data = ptr;

	return ret;
}


void gru_node_destroy(gru_node_t **node) {
	gru_node_unlink(*(node));
        
        free(*(node));
        *node = NULL;
}


void gru_node_set_previous(gru_node_t *node, gru_node_t *previous) {
	if (!node) {
		return;
	}

	node->previous = previous;

	if (previous) {
		previous->next = node;
	}
}


void gru_node_set_next(gru_node_t *node, gru_node_t *next) {
	if (!node) {
		return;
	}

	node->next = next;
	if (next) {
		next->previous = node;
	}
}


void gru_node_reset(gru_node_t *node) {
    node->previous = NULL;
    node->next = NULL;
}


void gru_node_unlink(gru_node_t *node) {
    
    if (!node) {
        return;
    }
    
    gru_node_set_next(node->previous, node->next);
    gru_node_set_previous(node->next, node->previous);
    
    gru_node_reset(node);
}