/*
 * Copyright 2017 Otavio Piske <angusyoung@gmail.com>.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdio.h>

#include "common/gru_colors.h"
#include "common/gru_portable.h"

#ifndef GRU_CLI_OPT_H
#define GRU_CLI_OPT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Prints CLI options help
 * @param long_opt long option
 * @param short_opt short option
 * @param desc description
 */
gru_export void gru_cli_option_help(
	const char *long_opt, const char *short_opt, const char *desc);

/**
 * Prints program usage for composed program types
 * @param appname Application name
 * @param program_name Program name
 */
gru_export void gru_cli_program_usage(const char *appname, const char *program_name);

/**
 * Prints program description for composed programs
 * @param appname Application name
 * @param description Description
 */
gru_export void gru_cli_program_description(const char *program, const char *description);

/**
 * Prints program basic usage
 * @param appname Application name
 */
gru_export void gru_cli_general_usage(const char *appname);

#ifdef __cplusplus
}
#endif

#endif /* GRU_CLI_OPT_H */
