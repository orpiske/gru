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
#ifndef GRU_COLORS_H
#define GRU_COLORS_H

/**
 * Color definitions for systems that support it
 */

#define BLACK "\x1B[00;30m"
#define RED "\x1B[00;31m"
#define GREEN "\x1B[00;32m"
#define YELLOW "\x1B[00;33m"
#define BLUE "\x1B[00;34m"
#define MAGENTA "\x1B[00;35m"
#define CYAN "\x1B[00;36m"
#define WHITE "\x1B[00;37m"

#define LIGHT_BLACK "\x1B[01;30m"
#define LIGHT_RED "\x1B[01;31m"
#define LIGHT_GREEN "\x1B[01;32m"
#define LIGHT_YELLOW "\x1B[01;33m"
#define LIGHT_BLUE "\x1B[01;34m"
#define LIGHT_MAGENTA "\x1B[01;35m"
#define LIGHT_CYAN "\x1B[01;36m"
#define LIGHT_WHITE "\x1B[01;37m"

#define BG_BLACK "\x1B[02;40m"
#define BG_RED "\x1B[02;41m"
#define BG_GREEN "\x1B[02;42m"
#define BG_YELLOW "\x1B[02;43m"
#define BG_BLUE "\x1B[02;44m"
#define BG_MAGENTA "\x1B[02;45m"
#define BG_CYAN "\x1B[02;46m"
#define BG_WHITE "\x1B[02;47m"

#define RESET "\x1B[00m"

#define CLEAR_LINE "\x1B[2K\r"
#define CLEAR_SCREEN "\x1B[1;1H\x1B[2J"

#endif // GRU_COLORS_H
