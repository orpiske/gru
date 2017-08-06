/*
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

#ifndef GRU_GRU_NET_H
#define GRU_GRU_NET_H

#include <common/gru_portable.h>

#include <network/contrib/sts_net.h>

/**
 * A wrapper around the STS net library
 */


#ifdef __cplusplus
extern "C" {
#endif

typedef sts_net_socket_t gru_net_socket_t;
typedef sts_net_set_t gru_net_set_t;

gru_export const char *gru_net_get_last_error();

gru_export int gru_net_init();

gru_export void gru_net_shutdown();

gru_export void gru_net_reset_socket(gru_net_socket_t *socket);

gru_export int gru_net_is_socket_valid(gru_net_socket_t *socket);

gru_export int gru_net_open_socket(gru_net_socket_t *socket, const char *host, const char *service);

gru_export void gru_net_close_socket(gru_net_socket_t *socket);

gru_export int gru_net_accept_socket(gru_net_socket_t *listen_socket, gru_net_socket_t *remote_socket);

gru_export int gru_net_send(gru_net_socket_t *socket, const void *data, int length);

gru_export int gru_net_recv(gru_net_socket_t *socket, void *data, int length);

gru_export void gru_net_init_socket_set(gru_net_set_t* set);

gru_export int gru_net_add_socket_to_set(gru_net_socket_t *socket, gru_net_set_t *set);

gru_export int gru_net_remove_socket_from_set(gru_net_socket_t *socket, gru_net_set_t *set);

gru_export int gru_net_check_socket_set(gru_net_set_t *set, const float timeout);

#ifdef __cplusplus
}
#endif

#endif //GRU_GRU_NET_H
