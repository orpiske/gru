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
    struct addrinfo *addr;
    SOCKET sock;
};


gru_sock_t gru_sock_new(gru_status_t *status) {
    gru_sock_t ret = {0};

	WORD version; 
	WSADATA wsaData; 

    version = MAKEWORD(2 , 2);
	
	if (WSAStartup(version, &wsaData) != 0) {
		gru_status_set(status, GRU_FAILURE, "Unable to initialize winsock");
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		gru_status_set(status, GRU_FAILURE, "Incorrect Winsock version");
	}

    return ret;
}