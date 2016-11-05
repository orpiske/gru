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
#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include <assert.h>

#include "gru_node.h"
#include "common/gru_status.h"
#include "common/gru_base.h"


typedef struct gru_list_t_ {
	gru_node_t *root;
	gru_node_t *current;
} gru_list_t;

typedef bool(*compare_function_t)(const void *, const void *data, void *result);
typedef void(*handle_function_t)(const gru_node_t *, void *);


/**
 * Creates a new list
 * @return A new gru_list_t object
 */
gru_list_t *gru_list_new(gru_status_t *status);

/**
 * Ensures that the list is properly destroyed
 * @param list the list to destroy
 */
void gru_list_destroy(gru_list_t **list);


/**
 * Returns the number of items in a list
 * @param list A given list to check the number of items
 * @return The number of items
 * @note The list must not be NULL
 */
uint32_t gru_list_count(const gru_list_t *list);


/**
 * Appends an item in the list
 * @param list The list to receive the new item
 * @param data The data for the new node
 * @note It's up to the application to make sure that the data pointer remains
 * valid throughout the lifetime of the list
 * @return A pointer to the new node
 */
const gru_node_t *gru_list_append(gru_list_t *list, const void *data);


/**
 * Inserts an item in the list
 * @param list The list to receive the new item
 * @param data The data for the new node
 * @param position The position to insert the data
 * @return A pointer to the new node
 */
gru_node_t *gru_list_insert(gru_list_t *list, const void *data, uint32_t position);


/**
 * Removes an item from a list
 * @param list The list to remove the item
 * @param position The position of the item to be removed
 * @return A pointer to the removed node
 */
gru_node_t *gru_list_remove(gru_list_t *list, uint32_t position);


/**
 * Removes a node that matches a given data as returned by comparable
 * @param list The list to remove the node from
 * @param comparable The comparison function (void *result will be NULL)
 * @param other The data to compare the node with
 * @return true if the node was removed or false if it was not found
 */
bool gru_list_remove_item(gru_list_t *list, compare_function_t comparable,
		const void *other);

/**
 * Gets a node from the list at the given position
 * @param list the list
 * @param position the position
 * @return the node or NULL if not existent
 */
const gru_node_t *gru_list_get(const gru_list_t *list, uint32_t position);


/**
 * Traverses the list comparing the data. It aborts if the uniqueness is true and
 * the comparison returns true
 * @param list
 * @param comparable
 * @param other
 * @param result
 */
void gru_list_for_each_compare(const gru_list_t *list, bool uniqueness,
		compare_function_t comparable, const void *compare, void *result);


/**
 * Traverses the list executing a set of operations depending on the result of a
 * comparison function
 * @param list The list to be traversed
 * @param comparable A comparison function. If NULL, then defaults to true
 * @param true_handle A function handle for when comparable returns true
 * @param false_handle A function handle for when comparable returns false. If
 * NULL then it will be ignored
 * @param data Payload data for the true_handle and false_handle functions
 */
void gru_list_for_each(const gru_list_t *list, handle_function_t handle, void *data);


/**
 * Traverses the list comparing the data. It aborts if the uniqueness is true and
 * the comparison returns true
 * @param list
 * @param comparable
 * @param other
 * @param result
 */
const void *gru_list_get_item(const gru_list_t *list, compare_function_t comparable, 
                          const void *other);




#endif
