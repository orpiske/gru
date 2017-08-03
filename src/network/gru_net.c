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

#include "gru_net.h"

const char* gru_net_get_last_error() {
    return sts_net_get_last_error();
}


int gru_net_init() {
    return sts_net_init();
}

void gru_net_shutdown() {
    sts_net_shutdown();
}

void gru_net_reset_socket(gru_net_socket_t* socket) {
    sts_net_reset_socket(socket);
}

int gru_net_is_socket_valid(gru_net_socket_t* socket) {
    return sts_net_is_socket_valid(socket);
}

int gru_net_open_socket(gru_net_socket_t *socket, const char *host, const char *service) {
    return sts_net_open_socket(socket, host, service);
}

void gru_net_close_socket(gru_net_socket_t *socket) {
    gru_net_close_socket(socket);
}

int gru_net_accept_socket(gru_net_socket_t *listen_socket, sts_net_socket_t *remote_socket) {
    return sts_net_accept_socket(listen_socket, remote_socket);
}


int gru_net_send(gru_net_socket_t *socket, const void *data, int length) {
    return sts_net_send(socket, data, length);
}

int gru_net_recv(gru_net_socket_t *socket, void *data, int length) {
    return sts_net_recv(socket, data, length);
}

void gru_net_init_socket_set(gru_net_set_t *set) {
    gru_net_init_socket_set(set);
}

int gru_net_add_socket_to_set(gru_net_socket_t *socket, gru_net_set_t *set) {
    return sts_net_add_socket_to_set(socket, set);
}

int gru_net_remove_socket_from_set(gru_net_socket_t *socket, gru_net_set_t *set) {
    return sts_net_remove_socket_from_set(socket, set);
}

int gru_net_check_socket_set(gru_net_set_t *set, const float timeout) {
    return sts_net_check_socket_set(set, timeout);
}