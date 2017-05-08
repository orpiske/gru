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

#ifndef GRU_SOCK_H
#define GRU_SOCK_H

#if !defined (__WIN32__) && !defined(__WIN64__)
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netdb.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>
#else
 #ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
 #endif // WIN32_LEAN_AND_MEAN
 
 #include <winsock2.h>
 #include <ws2tcpip.h>

#endif // !defined (__WIN32__) && !defined(__WIN64__)

#include "common/gru_status.h"


#ifdef __cplusplus
extern "C" {
#endif

struct gru_sock_t_;
typedef struct gru_sock_t_ gru_sock_t;

gru_export gru_sock_t gru_sock_new(gru_status_t *status);

gru_export void gru_sock_set_port(gru_sock_t *sock, uint16_t port);

gru_export bool gru_sock_open(gru_sock_t *sock, gru_status_t *status);

#ifdef __cplusplus
}
#endif

#endif /* GRU_SOCK_H */