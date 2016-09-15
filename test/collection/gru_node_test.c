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


static bool test_set_next() {
    uint32_t value1 = 10;
    uint32_t value2 = 20;
    
    gru_node_t *node1 = gru_node_new(&value1);
    gru_node_t *node2 = gru_node_new(&value2);
    
    gru_node_set_next(node1, node2);
    
    // A *very* simple test to check the circular relationship between the nodes
    
    uint32_t *d1 = (uint32_t *) node1->next->data;
    uint32_t *d2 = (uint32_t *) node2->previous->data;
    
    if (*d1 == 20) {
        if (*d2 == 10) {
            gru_node_destroy(&node1);
            gru_node_destroy(&node2);
            
            return true;
        }
    }
    gru_node_destroy(&node1);
    gru_node_destroy(&node2);
    
    return false;   
}


static bool test_set_previous() {
    uint32_t value1 = 10;
    uint32_t value2 = 20;
    
    gru_node_t *node1 = gru_node_new(&value1);
    gru_node_t *node2 = gru_node_new(&value2);
    
    gru_node_set_previous(node2, node1);
    
    // A *very* simple test to check the circular relationship between the nodes
    
    uint32_t *d1 = (uint32_t *) node1->next->data;
    uint32_t *d2 = (uint32_t *) node2->previous->data;
    
    if (*d1 == 20) {
        if (*d2 == 10) {
            gru_node_destroy(&node1);
            gru_node_destroy(&node2);
            
            return true;
        }
    }
    gru_node_destroy(&node1);
    gru_node_destroy(&node2);
    
    return false;   
}

/*
 * 
 */
int
main(int argc, char** argv)
{
    if (test_set_next()) {
        if (test_set_previous()) {
            return EXIT_SUCCESS;
        }
    }
    
    return EXIT_FAILURE;
}

