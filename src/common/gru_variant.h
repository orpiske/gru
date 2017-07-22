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
#ifndef GRU_VARIANT_H
#define GRU_VARIANT_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include <common/gru_alloc.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef enum gru_variant_type_t_ {
  GRU_STRING,
  GRU_INTEGER,
  GRU_DOUBLE,
  GRU_BOOLEAN,
} gru_variant_type_t;


/**
 * An abstract struct that can hold different types
 */
typedef struct gru_variant_t_ {
  gru_variant_type_t type;
  union {
	uint64_t inumber;
	long double fnumber;
	char *string;
	bool flag;
  } variant;
} gru_variant_t;


/**
 * Initializer for the string variant type
 */
#define GRU_VARIANT_STRING_INITIALIZER(x) { .type = GRU_STRING, .variant.string = x }

/**
 * Default string initializer
 */
#define GRU_VARIANT_STRING_DEFAULT_INITIALIZER GRU_VARIANT_STRING_INITIALIZER(NULL)

/**
 * Initializer for the integer variant type
 */
#define GRU_VARIANT_INTEGER_INITIALIZER(x) { .type = GRU_INTEGER, .variant.inumber = x }


/**
 * Default integer initializer
 */
#define GRU_VARIANT_INTEGER_DEFAULT_INITIALIZER GRU_VARIANT_INTEGER_INITIALIZER(0)

/**
 * Initializer for the double variant type
 */
#define GRU_VARIANT_DOUBLE_INITIALIZER(x) { .type = GRU_DOUBLE, .variant.fnumber = x }


/**
 * Default double initializer
 */
#define GRU_VARIANT_DOUBLE_DEFAULT_INITIALIZER GRU_VARIANT_DOUBLE_INITIALIZER(0.0)

/**
 * Initializer for the boolean variant type
 */
#define GRU_VARIANT_BOOLEAN_INITIALIZER(x) { .type = GRU_BOOLEAN, .variant.flag = x }


/**
 * Default boolean initializer
 */
#define GRU_VARIANT_BOOLEAN_DEFAULT_INITIALIZER GRU_VARIANT_BOOLEAN_INITIALIZER(false)



/**
 * Set the variant value to a string
 * @param variant the variant hold the data
 * @param str the string to set
 * @return false if unable to allocate memory for the string or true otherwise
 */
gru_export bool gru_variant_set_string(gru_variant_t *variant, const char *str);

/**
 * Set the variant value to an integer
 * @param variant the variant to hold the data
 * @param number the number to set
 */
gru_export void gru_variant_set_integer(gru_variant_t *variant, uint64_t number);

/**
 * Release the memory used by a variant (if any used at all). It's safe to
 * pass any variant even if no memory is used at all
 * @param variant the variant to release
 */
gru_export void gru_variant_clean(gru_variant_t *variant);

/**
 * Parses a string and sets it to the most appropriate type
 * @param str the string to parse
 * @return a variant (if all conversion fails, it defaults to string)
 */
gru_export gru_variant_t gru_variant_parse(const char *str);


/**
 * Simple equality check to test if the variant value matches a given string
 * @param variant the variant to compare with
 * @param str the string to check
 * @return true if it's equal or false otherwise
 */
bool gru_variant_equals_str(gru_variant_t *variant, const char *str);

#ifdef __cplusplus
}
#endif

#endif //GRU_VARIANT_H
