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
#include <log/gru_logger.h>
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

static conversion_stat_t gru_variant_try_uint(const char *str, uint64_t *out) {
	const int base = 10;
	char *end;

	errno = 0;
	*out = strtol(str, &end, base);

	if ((errno == ERANGE && (*out == LONG_MAX || *out == LONG_MIN)) || (errno != 0 && *out == 0)) {
		logger_t logger = gru_logger_get();
		logger(GRU_WARNING, "Cannot convert the value %s because it's out of range", str);

		return VAR_ERROR | VAR_OUT_OF_RANGE;
	}

	if (end == str || *end != '\0') {
		return VAR_ERROR | VAR_NOT_CONVERSIBLE;
	}

	return VAR_SUCCESS;
}

static conversion_stat_t gru_variant_try_double(const char *str, long double *out) {
	char *end;

	errno = 0;
	*out = strtold(str, &end);

	if (errno == ERANGE) {
		logger_t logger = gru_logger_get();
		logger(GRU_WARNING, "Cannot convert the value %s because it's out of range", str);

		return VAR_ERROR | VAR_OUT_OF_RANGE;
	}

	if (end == str || *end != '\0') {
		return VAR_ERROR | VAR_NOT_CONVERSIBLE;
	}

	return VAR_SUCCESS;
}


static conversion_stat_t gru_variant_try_bool(const char *str, bool *out) {
	if (strcmp(str, "true") == 0) {
		*out = true;

		return VAR_SUCCESS;
	}
	else {
		if (strcmp(str, "false") == 0) {
			*out = false;

			return VAR_SUCCESS;
		}
	}

	return VAR_ERROR | VAR_NOT_CONVERSIBLE;
}

gru_variant_t gru_variant_parse(const char *str) {
	gru_variant_t var = {0};
	conversion_stat_t ret;

	if (str) {
		ret = gru_variant_try_uint(str, &var.variant.inumber);
		if (ret == VAR_SUCCESS) {
			var.type = GRU_INTEGER;

			return var;
		}

		ret = gru_variant_try_double(str, &var.variant.fnumber);
		if (ret == VAR_SUCCESS) {
			var.type = GRU_DOUBLE;

			return var;
		}

		ret = gru_variant_try_bool(str, &var.variant.flag);
		if (ret == VAR_SUCCESS) {
			var.type = GRU_BOOLEAN;

			return var;
		}
	}

	gru_variant_set_string(&var, str);

	return var;
}

bool gru_variant_equals_str(gru_variant_t *variant, const char *str) {
	if (!variant) {
		return false;
	}

	if (variant->type != GRU_STRING) {
		return false;
	}

	if (strcmp(variant->variant.string, str) == 0) {
		return true;
	}

	return false;
}