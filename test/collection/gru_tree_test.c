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
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

#include "collection/gru_node.h"
#include "collection/gru_list.h"
#include "collection/gru_tree.h"

static gru_tree_node_t *build_paths() {
    gru_tree_node_t *root = gru_tree_new("/");

    gru_tree_node_t *usr = gru_tree_add_child(root, "usr");
    gru_tree_node_t *opt = gru_tree_add_child(root, "opt");
    gru_tree_node_t *var = gru_tree_add_child(root, "var");
    gru_tree_node_t *dev = gru_tree_add_child(root, "dev");

    gru_tree_node_t *usr_bin = gru_tree_add_child(usr, "bin");
    gru_tree_node_t *opt_other = gru_tree_add_child(opt, "other");

    gru_tree_node_t *var_log = gru_tree_add_child(var, "log");
    gru_tree_node_t *var_log_a = gru_tree_add_child(var_log, "a");
    gru_tree_node_t *var_log_a_b = gru_tree_add_child(var_log_a, "b");
    gru_tree_node_t *var_log_a_c = gru_tree_add_child(var_log_a_b, "c");

    return root;
}

bool compare_file_name(const void *current, const void *data, void *result) {
    printf("Comparing %s with %s\n", (const char *) current, (const char *) data);
    if (strcmp((const char *) current, (const char *) data) == 0) {
        return true;
    }

    return false;
}


void print_path(const void *nodedata, void *data) {
    printf("\t%s\n", (const char *) nodedata);
}

void print_path2(const void *nodedata, void *data) {
    printf("\t%s\n", (char *) ((gru_tree_node_t *) nodedata)->data);
}


int main(int argc, char **argv) {
    gru_tree_node_t *root = build_paths();

    uint32_t count = gru_tree_count(root);

    if (count != 11) {
        fprintf(stderr, "Expected 11 nodes but got %d\n", count);
        return EXIT_FAILURE;
    }

    uint32_t children = gru_tree_count_children(root);
    if (children != 4) {
        fprintf(stderr, "Expected 4 children nodes but got %d\n", children);
        return EXIT_FAILURE;
    }

    const gru_tree_node_t *c = gru_tree_search(root, compare_file_name, "c");

    gru_tree_for_each(root, print_path, NULL);

    printf("Printing childs of var\n");
    gru_tree_for_each_child(root, print_path, NULL);
    printf("Done");

    gru_tree_remove_child(root, compare_file_name, "var");
    count = gru_tree_count(root);
    if (count != 6) {
        fprintf(stderr, "Expected 7 nodes after removing var but got %d\n", count);
        return EXIT_FAILURE;
    }

    gru_tree_for_each(root, print_path, NULL);

    gru_tree_search(root, compare_file_name, "c");

    gru_tree_for_each(root, print_path, NULL);

    gru_tree_destroy(&root);


    return EXIT_SUCCESS;
}
