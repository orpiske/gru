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
		if (!variant->variant.string) {
			return false;
		}
	}
	else {
		variant->variant.string = NULL;
	}

	return true;
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

typedef enum conversion_stat_t_ {
  VAR_ERROR = 0,
  VAR_SUCCESS = 1,
  VAR_OUT_OF_RANGE = 2,
  VAR_NOT_CONVERSIBLE = 4,
} conversion_stat_t;

static conversion_stat_t gru_variant_try_uint(const char *str, uint64_t *out, gru_status_t *status) {
	const int base = 10;
	char *end;

	errno = 0;
	*out = strtol(str, &end, base);

	if ((errno == ERANGE && (*out == LONG_MAX || *out == LONG_MIN)) || (errno != 0 && *out == 0)) {
		gru_status_set(status, GRU_FAILURE, "Out of range");

		return VAR_ERROR | VAR_OUT_OF_RANGE;
	}

	if (end == str || *end != '\0') {
		return VAR_ERROR | VAR_NOT_CONVERSIBLE;
	}

	return VAR_SUCCESS;
}

static conversion_stat_t gru_variant_try_double(const char *str, long double *out, gru_status_t *status) {
	char *end;

	errno = 0;
	*out = strtold(str, &end);

	if (errno == ERANGE) {
		gru_status_set(status, GRU_FAILURE, "Out of range");

		return VAR_ERROR | VAR_OUT_OF_RANGE;
	}

	if (end == str || *end != '\0') {
		return VAR_ERROR | VAR_NOT_CONVERSIBLE;
	}

	return VAR_SUCCESS;
}

gru_variant_t gru_variant_parse(const char *str, gru_status_t *status) {
	gru_variant_t var = {0};
	conversion_stat_t ret;

	ret = gru_variant_try_uint(str, &var.variant.inumber, status);
	if (ret == VAR_SUCCESS) {
		var.type = GRU_INTEGER;

		return var;
	}

	ret = gru_variant_try_double(str, &var.variant.fnumber, status);
	if (ret == VAR_SUCCESS) {
		var.type = GRU_DOUBLE;

		return var;
	}

	gru_variant_set_string(&var, str);

	return var;
}