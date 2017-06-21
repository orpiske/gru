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
#include "gru_variant.h"

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

inline void gru_keypair_destroy_list_item(void **ptr) {
	gru_keypair_destroy((gru_keypair_t **) ptr);
}

bool gru_keypair_set_key(gru_keypair_t *kp, const char *key) {
	kp->key = strdup(key);

	if (kp->key) {
		return true;
	}

	return false;
}

gru_keypair_t *gru_keypair_clone(gru_keypair_t *kp, gru_status_t *status) {
	gru_keypair_t *ret = gru_keypair_new(status);
	if (!ret) {
		return NULL;
	}

	ret->key = strdup(kp->key);
	ret->pair->type = kp->pair->type;

	if (ret->pair->type == GRU_STRING) {
		if (kp->pair->variant.string) {
			ret->pair->variant.string = strdup(kp->pair->variant.string);
		}
		else {
			ret->pair->variant.string = kp->pair->variant.string;
		}
	}
	else {
		ret->pair->variant.inumber = kp->pair->variant.inumber;
	}

	return ret;
}

bool gru_keypair_key_equals(gru_keypair_t *kp, const char *key) {
	if (strcmp(kp->key, key) == 0) {
		return true;
	}

	return false;
}

#if !defined(HAVE_STRNDUP)
char *strndup(const char *source, size_t limit);
#endif // HAVE_STRNDUP

gru_keypair_t *gru_keypair_parse(const char *str, gru_status_t *status) {
	gru_keypair_t *ret = gru_keypair_new(status);
	gru_alloc_check(ret, NULL);

	size_t len = strlen(str);
	uint32_t last = 0;
	for (int i = 0; i <= len; i++) {
		if (str[i] == '=' || str[i] == 0) {
			ret->key = strndup(str, i);

			ret->pair->type = GRU_STRING;

			size_t after_sep = i + 1;
			if (after_sep < len) {
				ret->pair->variant.string = strdup(str + after_sep);
			}
			else {
				gru_keypair_destroy(&ret);

				gru_status_set(status, GRU_FAILURE, "Invalid key/pair string: %s", str);

				return NULL;
			}

			break;
		}
	}

	return ret;
}