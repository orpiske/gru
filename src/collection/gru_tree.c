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
#include "gru_tree.h"

gru_tree_node_t *gru_tree_new(const void *data) {
	gru_tree_node_t *ret = malloc(sizeof(gru_tree_node_t));

	if (!ret) {
		fprintf(stderr, "Not enough memory to allocate for new node\n");

		return NULL;
	}

	ret->children = gru_list_new(NULL);
	if (!ret->children) {
		gru_tree_destroy(&ret);

		return NULL;
	}

	ret->data = data;

	return ret;
}

static void gru_tree_node_destroy_child(const void *data, void *ptr) {
	gru_tree_node_t *node = (gru_tree_node_t *) data;

	gru_tree_destroy(&node);
}

void gru_tree_destroy(gru_tree_node_t **ptr) {
	gru_tree_node_t *node = *ptr;

	if (!node) {
		return;
	}

	if (node->children) {
		gru_list_for_each(node->children, gru_tree_node_destroy_child, NULL);
		gru_list_destroy(&node->children);
	}

	free(node);
	node = NULL;
}

gru_tree_node_t *gru_tree_add_child(gru_tree_node_t *node, const void *data) {
	gru_tree_node_t *child = gru_tree_new(data);

	if (!child) {
		return NULL;
	}

	const gru_node_t *ret = gru_list_append(node->children, child);
	if (!ret) {
		gru_tree_destroy(&child);

		return NULL;
	}

	return child;
}

const gru_tree_node_t *gru_tree_search(gru_tree_node_t *node,
	compare_function_t comparable,
	const void *other) {
	if (!node) {
		return NULL;
	}

	if (!node->children) {
		return NULL;
	}

	if (comparable(node->data, other, NULL)) {
		return node;
	}

	gru_node_t *child_node = node->children->root;
	while (child_node) {
		gru_tree_node_t *tn = gru_node_get_data_ptr(gru_tree_node_t, child_node);

		const gru_tree_node_t *ret = gru_tree_search(tn, comparable, other);

		if (ret) {
			return ret;
		}

		child_node = child_node->next;
	}

	return NULL;
}

bool gru_tree_remove_child(gru_tree_node_t *node,
	compare_function_t comparable,
	const void *other) {
	if (!node) {
		return false;
	}

	if (!node->children) {
		return false;
	}

	if (comparable(node->data, other, NULL)) {
		return true;
	}

	gru_node_t *child_node = node->children->root;
	uint32_t pos = 0;
	while (child_node) {
		gru_tree_node_t *tn = gru_node_get_data_ptr(gru_tree_node_t, child_node);

		if (comparable(tn->data, other, NULL)) {
			gru_node_t *n = gru_list_remove(node->children, pos);
			gru_node_destroy(&n);
			gru_tree_destroy(&tn);
			return true;
		}

		child_node = child_node->next;
		pos++;
	}

	return false;
}

const gru_tree_node_t *
	gru_tree_for_each(gru_tree_node_t *node, tree_callback_fn callback, void *payload) {
	if (!node) {
		return NULL;
	}

	if (!node->children) {
		return NULL;
	}

	callback(node->data, payload);

	gru_node_t *child_node = node->children->root;
	while (child_node) {
		gru_tree_node_t *tn = gru_node_get_data_ptr(gru_tree_node_t, child_node);

		const gru_tree_node_t *ret = gru_tree_for_each(tn, callback, payload);

		if (ret) {
			return ret;
		}

		child_node = child_node->next;
	}

	return NULL;
}

typedef struct gru_tree_node_wrapper_t_ {
	void *payload;
	tree_callback_fn callback;
} gru_tree_wrapper_t;

/**
 * Long story short: since the implementation uses a gru_list_t * to hold the
 * children, the call to gru_tree_for_each_child uses gru_list_for_each to
 * iterate over the children. Since it gru_tree_node_t pointers are stored in
 * the children list, it is necessary to unwrap it and provide the pointer to
 * the data structure for the callback functions.
 */
static void gru_tree_for_each_wrapper(const void *ptr, void *envelope) {
	gru_tree_node_t *node = (gru_tree_node_t *) ptr;
	gru_tree_wrapper_t *wrapper = (gru_tree_wrapper_t *) envelope;

	wrapper->callback(node->data, wrapper->payload);
}

void gru_tree_for_each_child(gru_tree_node_t *node,
	tree_callback_fn callback,
	void *payload) {
	if (!node) {
		return;
	}

	if (!node->children) {
		return;
	}

	/*
	 * See the comments in gru_tree_for_each_wrapper for details about why
	 * the data and the callback are wrapped
	 */
	gru_tree_wrapper_t wrapper = {
		.payload = payload, .callback = callback,
	};

	gru_list_for_each(node->children, gru_tree_for_each_wrapper, &wrapper);
}

uint32_t gru_tree_count_children(gru_tree_node_t *node) {
	if (!node) {
		return 0;
	}

	if (!node->children) {
		return 0;
	}

	return gru_list_count(node->children);
}

static void gru_tree_count_int(const void *nodeptr, void *payload) {
	uint32_t *count = (uint32_t *) payload;

	(*count)++;
}

uint32_t gru_tree_count(gru_tree_node_t *node) {
	uint32_t ret = 0;
	gru_tree_for_each(node, gru_tree_count_int, &ret);

	return ret;
}

const gru_tree_node_t *gru_tree_search_child(gru_tree_node_t *node,
	compare_function_t comparable,
	const void *other) {
	if (!node) {
		return NULL;
	}

	if (!node->children) {
		return NULL;
	}

	gru_node_t *child_node = node->children->root;
	while (child_node) {
		gru_tree_node_t *tn = gru_node_get_data_ptr(gru_tree_node_t, child_node);

		bool ret = comparable(tn->data, other, NULL);
		if (ret) {
			return tn;
		}

		child_node = child_node->next;
	}

	return NULL;
}