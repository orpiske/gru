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
#ifndef GRU_TREE_H
#define GRU_TREE_H

#include "gru_collection_callbacks.h"
#include "gru_list.h"
#include "gru_node.h"

#include "common/gru_portable.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * An extremely simple unbalanced tree implementation
 */

typedef struct gru_tree_node_t_ {
	gru_list_t *children;
	const void *data;
} gru_tree_node_t;

/**
 * Creates a new tree and returns a pointer to the root node
 * @param data The data for the root node
 * @return A pointer to the root node
 */
gru_export gru_tree_node_t *gru_tree_new(const void *data);

/**
 * Destroys a tree node and all it's descendants
 * @param ptr A pointer-to-pointer for the node to destroy
 */
gru_export void gru_tree_destroy(gru_tree_node_t **ptr);

/**
 * Adds a child node to a given node.
 * @param node The node to add the child to
 * @param data The data to add to the child
 * @return A pointer to the newly added node. This node does *NOT* need to be
 * free'd. It will be free'd along with its parent
 */
gru_export gru_tree_node_t *gru_tree_add_child(gru_tree_node_t *node, const void *data);

/**
 * Searches the tree using DFS
 * @param node The starting node for the search
 * @param comparable A comparator function
 * @param other The data to compare to
 * @return A pointer to the node or NULL if not found
 */
gru_export const gru_tree_node_t *gru_tree_search(gru_tree_node_t *node,
	compare_function_t comparable,
	const void *other);

/**
 * Searches only the immediate children of the node
 * @param node The starting node for the search
 * @param comparable A comparator function
 * @param other The data to compare to
 * @return A pointer to the node or NULL if not found
 */
gru_export const gru_tree_node_t *gru_tree_search_child(gru_tree_node_t *node,
	compare_function_t comparable,
	const void *other);

/**
 * Removes a direct descendant of a node
 * @param node The parent node
 * @param comparable A comparator function
 * @param other The data to compare to
 * @return true if removed or false otherwise
 */
gru_export bool gru_tree_remove_child(gru_tree_node_t *node,
	compare_function_t comparable,
	const void *other);

/**
 * Traverses the tree executing a set of operations
 * @param node The starting node for the search
 * @param callback A callback function to be executed for all the nodes
 * @param payload Payload data to be passed to the passed to the callback
 * @return A pointer to the node or NULL if not found
 */
gru_export const gru_tree_node_t *
	gru_tree_for_each(gru_tree_node_t *node, tree_callback_fn callback, void *payload);

/**
 * Executes an operation on each child of the given node
 * @param node The starting node for the search
 * @param callback A callback function to be executed for all the nodes
 * @param payload Payload data to be passed to the passed to the callback
 */
gru_export void gru_tree_for_each_child(gru_tree_node_t *node,
	tree_callback_fn callback,
	void *payload);

/**
 * Returns the number of children of a node
 * @param node The node to count the number of children
 * @return The number of items
 * @note The node must not be NULL, otherwise it returns 0
 */
gru_export uint32_t gru_tree_count_children(gru_tree_node_t *node);

/**
 * Returns the number of children of a tree
 * @param node The node to count the number of children
 * @return The number of items
 * @note The node must not be NULL, otherwise it returns 0
 */
gru_export uint32_t gru_tree_count(gru_tree_node_t *node);

#ifdef __cplusplus
}
#endif

#endif /* GRU_TREE_H */
