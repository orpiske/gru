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
#include "gru_tree.h"

gru_tree_node_t *gru_tree_new(const void *data) {
    gru_tree_node_t *ret = malloc(sizeof (gru_tree_node_t));

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

gru_tree_node_t *gru_tree_add_child(gru_tree_node_t *node,
        const void *data) {
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
        gru_tree_node_t *tn = gru_node_get_data_ptr(gru_tree_node_t,
                child_node);

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
        gru_tree_node_t *tn = gru_node_get_data_ptr(gru_tree_node_t,
                child_node);


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


const gru_tree_node_t *gru_tree_for_each(gru_tree_node_t *node, 
                            tree_callback_fn callback, 
                            void *payload)
{
    if (!node) {
        return NULL;
    }

    if (!node->children) {
        return NULL;
    }

    callback(node->data, payload);

    gru_node_t *child_node = node->children->root;
    while (child_node) {
        gru_tree_node_t *tn = gru_node_get_data_ptr(gru_tree_node_t,
                child_node);

        gru_tree_node_t *ret = gru_tree_for_each(tn, callback, payload);

        if (ret) {
            return ret;
        }

        child_node = child_node->next;
    }

    return NULL;
}