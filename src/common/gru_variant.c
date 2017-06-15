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
#include "gru_variant.h"

bool gru_variant_set_string(gru_variant_t *variant, const char *str) {
	variant->type = GRU_STRING;
	if (str) {
		variant->variant.string = strdup(str);
	}
	else {
		variant->variant.string = NULL;
	}
}

void gru_variant_set_integer(gru_variant_t *variant, uint64_t number) {
	variant->type = GRU_INTEGER;
	variant->variant.inumber = number;
}

void gru_variant_clean(gru_variant_t *variant) {
	if (!variant) {
		return;
	}

	if (variant->type == GRU_STRING) {
		gru_dealloc_string(&variant->variant.string);
	}
}