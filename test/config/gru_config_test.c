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
#include <inttypes.h>
#include <string.h>

#include "config/gru_config.h"

typedef struct test_options_t_
{
    int32_t value1;
    char value2[32];
    int16_t value3;
} test_options_t;

void initialize_options(void *data) {
    test_options_t *options = (test_options_t *) data;
    
    options->value1 = 1981;
    bzero(options->value2, sizeof(options->value2));
    snprintf(options->value2, sizeof(options->value2), "%s", "sample value");
    options->value3 = 16;
}

void save_options(FILE *file, void *data) {
    test_options_t *options = (test_options_t *) data;
    
    fprintf(file, "value1=%hi\n", options->value1);
    fprintf(file, "value2=%s\n", options->value2);
    fprintf(file, "value3=%hi\n", options->value3);
    fflush(file);
}

void read_options(FILE *file, void *data) {
    test_options_t *options = (test_options_t *) data;

    gru_config_read_int(&options->value1, file, "value1");
    gru_config_read_char(options->value2, file, "value2");
    gru_config_read_short(&options->value3, file, "value3");
}

int test_write_init(int argc, char** argv)
{
    /*
     * gru_config_init(const char *dir, const char *filename, 
                              void *payload, gru_status_t *status)
     */
    test_options_t options = {0};
    gru_status_t status = {0};
    
    gru_payload_t *payload = gru_payload_init(initialize_options, 
                                              save_options, read_options,
                                              &options,
                                              &status);
    
    if (!payload) {
        fprintf(stderr, "Unable to initialize the payload: %s\n", 
                status.message);
        
        gru_payload_destroy(&payload);
        return EXIT_FAILURE;
    }
    
    gru_config_t *config = gru_config_init(".", "test.cfg", payload,
                                           &status);

    if (!config) {
        fprintf(stderr, "Unable to initialize the configuration: %s\n",
                status.message);

        gru_payload_destroy(&payload);
        return EXIT_FAILURE;
    }
    
    if (!gru_path_fexists(fileno(config->file), &status)) {
        if (status.code != GRU_SUCCESS) {
            fprintf(stderr, "Unable to check if file exists: %s\n", 
                    status.message);
        }

        gru_payload_destroy(&payload);
        gru_config_destroy(&config);
        return EXIT_FAILURE;
    }
   

    gru_payload_destroy(&payload);
    gru_config_destroy(&config);
    return EXIT_SUCCESS;
}

int test_read_init(int argc, char** argv)
{
    /*
     * gru_config_init(const char *dir, const char *filename, 
                              void *payload, gru_status_t *status)
     */
    test_options_t options = {0};
    gru_status_t status = {0};
    
    gru_payload_t *payload = gru_payload_init(initialize_options, 
                                              save_options, read_options,
                                              &options,
                                              &status);
    
    if (!payload) {
        fprintf(stderr, "Unable to initialize the payload: %s\n", 
                status.message);
        
        gru_payload_destroy(&payload);
        return EXIT_FAILURE;
    }
    
    gru_config_t *config = gru_config_init(".", "test.cfg", payload,
                                           &status);

    if (!config) {
        fprintf(stderr, "Unable to initialize the configuration: %s\n",
                status.message);

        gru_payload_destroy(&payload);
        return EXIT_FAILURE;
    }
    
    if (!gru_path_fexists(fileno(config->file), &status)) {
        if (status.code != GRU_SUCCESS) {
            fprintf(stderr, "Unable to check if file exists: %s\n", 
                    status.message);
        }

        gru_payload_destroy(&payload);
        gru_config_destroy(&config);
        return EXIT_FAILURE;
    }
   
    
    if (options.value1 != 1981) {
        fprintf(stderr, "Invalid value for option.value1: %i\n", options.value1);
        
        return EXIT_FAILURE;
    }
    
    if (strncmp(options.value2, "sample value", strlen("sample value")) != 0) {
        fprintf(stderr, "Invalid value for option.value2: %s\n", options.value2);
        
        return EXIT_FAILURE;
    }
    
    if (options.value3 != 16) {
        fprintf(stderr, "Invalid value for option.value3: %i\n", options.value3);
        
        return EXIT_FAILURE;
    }

    gru_payload_destroy(&payload);
    gru_config_destroy(&config);
    return EXIT_SUCCESS;
}


int main(int argc, char** argv)
{
    if (argc == 2) {
        if (strcmp(argv[1], "read") == 0) {
            return test_read_init(argc, argv);
        }
        else {
            return test_write_init(argc, argv);
        }
    }
}
