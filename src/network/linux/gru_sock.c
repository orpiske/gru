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
#include "network/gru_sock.h"

struct gru_sock_t_ {
    struct sockaddr_in addrinfo;
    int sock;
    struct hostent hostinfo;
};

gru_sock_t gru_sock_new(gru_status_t *status) {
    gru_sock_t ret = {0};

    ret.addrinfo.sin_family = AF_INET;
    ret.sock = -1;
    
    return ret;
}

void gru_sock_set_port(gru_sock_t *sock, uint16_t port) {
    sock->addrinfo.sin_port = htons(port);
}

bool gru_sock_open(gru_sock_t *sock, gru_status_t *status) {
    return false;
}