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
#if !defined(_WIN32) && !defined(_WIN64)
#define likely(x) __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)
#define gru_export
#define gru_restrict restrict
#define gru_attr_unused __attribute__((unused))
#else
#define likely(x) (x)
#define unlikely(x) (x)
#define bzero(b, len) (memset((b), '\0', (len)), (void) 0)
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#define strerror_r(errno, buf, len) strerror_s(buf, len, errno)
#define gru_export __declspec(dllexport)
#define gru_restrict
#define gru_attr_unused
#endif
