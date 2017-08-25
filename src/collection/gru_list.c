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
#include "gru_list.h"

gru_list_t *gru_list_new(gru_status_t *status) {
	gru_list_t *ret = (gru_list_t *) malloc(sizeof(gru_list_t));

	if (!ret) {
		if (status) {
			gru_status_set(
				status, GRU_FAILURE, "Not enough memory to allocate for a new list");
		}

		return NULL;
	}

	ret->root = NULL;

	return ret;
}

void gru_list_destroy(gru_list_t **list) {
	if ((*list) == NULL) {
		return;
	}

	gru_node_t *node = (*list)->root;

	while (node) {
		gru_node_t *next = node->next;
		gru_node_destroy(&node);

		node = next;
	}

	free(*list);
	*list = NULL;
}

inline static bool can_continue(uint32_t count, uint32_t position) {
	if (likely(count < position)) {
		return true;
	}

	return false;
}

static gru_node_t *go_to(const gru_list_t *list, uint32_t position, uint32_t *count) {
	gru_node_t *node = list->root;

	*count = 0;
	while (node && can_continue(*count, position)) {
		node = node->next;
		(*count)++;
	}

	return node;
}

static gru_node_t *go_to_end(gru_list_t *list) {
	gru_node_t *node = list->root;

	while (node && node->next) {
		node = node->next;
	}

	return node;
}

uint32_t gru_list_count(const gru_list_t *list) {
	uint32_t count = 0;
	gru_node_t *node = NULL;

	if (list == NULL) {
		return 0;
	}

	node = list->root;
	while (node) {
		node = node->next;
		count++;
	}

	return count;
}

const gru_node_t *gru_list_append(gru_list_t *list, const void *data) {
	gru_node_t *last = go_to_end(list);
	gru_node_t *node = gru_node_new(data);

	if (!node) {
		return NULL;
	}

	if (!last) {
		list->root = node;
	} else {
		gru_node_set_next(last, node);
		gru_node_set_previous(node, last);
	}

	return node;
}

gru_node_t *gru_list_insert(gru_list_t *list, const void *data, uint32_t position) {
	gru_node_t *current = NULL;
	uint32_t count = 0;

	current = go_to(list, position, &count);
	if (count != position) {
		return NULL;
	}

	gru_node_t *node = gru_node_new(data);
	if (current == NULL) {
		list->root = node;
	} else {
		gru_node_set_next(current->previous, node);
		gru_node_set_previous(node, current->previous);

		gru_node_set_previous(current, node);
		gru_node_set_next(node, current);
	}

	return node;
}

gru_node_t *gru_list_remove(gru_list_t *list, uint32_t position) {
	uint32_t count = 0;

	gru_node_t *node = go_to(list, position, &count);
	if (count != position) {
		return NULL;
	}

	if (node == NULL) {
		return node;
	}

	if (position == 0) {
		list->root = node->next;
	}

	gru_node_unlink(node);

	return node;
}


gru_node_t *gru_list_remove_node(gru_list_t *list, gru_node_t *node) {
	if (!list->root || !node) {
		return NULL;
	}

	if (node == list->root) {
		list->root = list->root->next;
		gru_node_unlink(node);
		return node;
	}

	gru_node_t *curr = list->root;

	while (curr) {
		if (curr == node) {
			gru_node_unlink(node);
			return node;
		}
		curr = curr->next;
	}

	return NULL;
}

bool gru_list_remove_item(gru_list_t *list,
	compare_function_t comparable,
	const void *other) {
	gru_node_t *node = NULL;

	if (list == NULL) {
		return false;
	}

	node = list->root;

	while (node) {
		bool ret = comparable(node->data, other, NULL);
		if (ret == true) {
			gru_node_unlink(node);

			free(node);

			return true;
		}

		node = node->next;
	}

	return false;
}

const gru_node_t *gru_list_get(const gru_list_t *list, uint32_t position) {
	uint32_t count = 0;

	gru_node_t *node = go_to(list, position, &count);
	if (count != position) {
		return NULL;
	}

	return node;
}

void gru_list_for_each_compare(const gru_list_t *list,
	bool uniqueness,
	compare_function_t comparable,
	const void *other,
	void *result) {
	gru_node_t *node = NULL;

	if (list == NULL) {
		return;
	}

	node = list->root;

	while (node) {
		bool ret = comparable(node->data, other, result);
		if (ret == true && uniqueness == true) {
			return;
		}

		node = node->next;
	}
}

void gru_list_for_each(const gru_list_t *list, handle_function_t handle, void *data) {
	gru_node_t *node = NULL;

	if (list == NULL) {
		return;
	}

	node = list->root;

	while (node) {
		handle(node->data, data);

		node = node->next;
	}
}

void gru_list_for_each_ex(const gru_list_t *list,
	handle_function_info_t handle,
	void *data) {
	gru_node_t *node = NULL;

	if (list == NULL) {
		return;
	}

	node = list->root;

	uint32_t pos = 0;
	while (node) {
		gru_node_info_t info = {
			.parent_pos = 0, .self_pos = pos,
		};

		handle(node->data, info, data);

		node = node->next;
		pos++;
	}
}

const void *gru_list_get_item(const gru_list_t *list,
	compare_function_t comparable,
	const void *other) {
	gru_node_t *node = NULL;

	if (list == NULL) {
		return NULL;
	}

	node = list->root;

	while (node) {
		bool ret = comparable(node->data, other, NULL);
		if (ret == true) {
			return node->data;
		}

		node = node->next;
	}

	return NULL;
}

struct gru_list_pl {
	gru_nodedata_destructor destructor;
};

static void gru_list_node_destroy(const void *nodedata, void *payload) {
	if (payload) {
		struct gru_list_pl *pl = (struct gru_list_pl *) payload;

		pl->destructor((void **) &nodedata);
	}
}

void gru_list_clean(gru_list_t *list, gru_nodedata_destructor destructor) {
	if (list) {
		struct gru_list_pl pl;

		pl.destructor = destructor;
		gru_list_for_each(list, gru_list_node_destroy, &pl);
	}
}