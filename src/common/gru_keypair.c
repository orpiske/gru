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
#include "gru_keypair.h"

gru_keypair_t *gru_keypair_new(gru_status_t *status) {
	gru_keypair_t *kp = gru_alloc(sizeof(gru_keypair_t), status);
	gru_alloc_check(kp, NULL);

	kp->pair = gru_alloc(sizeof(gru_variant_t), status);
	if (!kp->pair) {
		gru_dealloc((void **) &kp);

		return NULL;
	}

	return kp;
}


void gru_keypair_destroy(gru_keypair_t **ptr) {
	gru_keypair_t *kp = *ptr;

	if (kp) {
		gru_variant_clean(kp->pair);
	}

	gru_dealloc_string(&kp->key);

	gru_dealloc((void **) &kp->pair);
	gru_dealloc((void **) ptr);
}

bool gru_keypair_set_key(gru_keypair_t *kp, const char *key) {
	kp->key = strdup(key);
}