/*
 Copyright 2017 Otavio Rodolfo Piske

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

#ifndef GRU_KEYPAIR_H
#define GRU_KEYPAIR_H

#include <stdint.h>
#include <string.h>

#include "gru_status.h"
#include "gru_variant.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A key/pair structure
 */
typedef struct gru_keypair_t_ {
  char *key;
  gru_variant_t *pair;
} gru_keypair_t;

/**
 * Creates a new key/pair struct
 * @param status
 * @return
 */
gru_keypair_t *gru_keypair_new(gru_status_t *status);

/**
 * Destroys a key/pair struct
 * @param ptr
 */
void gru_keypair_destroy(gru_keypair_t **ptr);

/**
 * Destructor wrapper for gru_list_clean
 * @param ptr
 */
inline static void gru_keypair_destroy_list_item(void **ptr) {
	gru_keypair_destroy((gru_keypair_t **) ptr);
}


/**
 * Sets the key
 * @param kp
 * @param key
 * @return
 */
bool gru_keypair_set_key(gru_keypair_t *kp, const char *key);


/**
 * Clone a key/pair struct
 * @param kp
 * @param status
 * @return
 */
gru_keypair_t *gru_keypair_clone(gru_keypair_t *kp, gru_status_t *status);


/**
 * Checks whether a key/pair struct matches the key
 * @param kp
 * @param key
 * @return
 */
bool gru_keypair_key_equals(gru_keypair_t *kp, const char *key);


/**
 * Parse a string in the format key=pair and returns an gru_keypair_t
 * @param str
 * @param status
 * @return
 */
gru_keypair_t *gru_keypair_parse(const char *str, gru_status_t *status);

#ifdef __cplusplus
}
#endif

#endif //GRU_KEYPAIR_H
