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
#include "gru_cli_opt.h"

void gru_cli_option_help(const char *long_opt, const char *short_opt, const char *desc) {
	printf("\t%s%s--%s (-%s short option) %s\n\t\t%s\n\n", RESET, LIGHT_WHITE, long_opt,
		short_opt, RESET, desc);
}

void gru_cli_program_usage(const char *appname, const char *program_name) {
	printf("%s%sUsage:%s\n%s %s <options>\n\nValid options:\n\n", RESET, LIGHT_WHITE,
		RESET, appname, program_name);
}


void gru_cli_program_description(const char *program, const char *description) {
	printf("\t%s%s%-15s%s\t%s\n", RESET, LIGHT_WHITE, program, RESET, description);
}


void gru_cli_general_usage(const char *appname) {
	printf("%s%sUsage:%s\n%s <program> <options>\n\nValid programs:\n\n", RESET,
		LIGHT_WHITE, appname, RESET);
}