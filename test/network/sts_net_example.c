/*
  This is free and unencumbered software released into the public domain.

  Anyone is free to copy, modify, publish, use, compile, sell, or
  distribute this software, either in source code form or as a compiled
  binary, for any purpose, commercial or non-commercial, and by any
  means.

  In jurisdictions that recognize copyright laws, the author or authors
  of this software dedicate any and all copyright interest in the
  software to the public domain. We make this dedication for the benefit
  of the public at large and to the detriment of our heirs and
  successors. We intend this dedication to be an overt act of
  relinquishment in perpetuity of all present and future rights to this
  software under copyright law.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.

  For more information, please refer to <http://unlicense.org/>
*/

#include <stdlib.h>
#include <stdio.h>

#include <network/contrib/sts_net.h>


void panic(const char* msg) {
  fprintf(stderr, "PANIC: %s\n\n", msg);
  exit(EXIT_FAILURE);
}


int main(int argc, char *argv[]) {
  int               i, j, bytes;
  sts_net_set_t     set;
  sts_net_socket_t  server;
  sts_net_socket_t  clients[STS_NET_SET_SOCKETS];
  char              buffer[256];

  (void)(argc);
  (void)(argv);

  for (i = 0; i < STS_NET_SET_SOCKETS; ++i) {
    clients[i].ready = 0;
    clients[i].fd = INVALID_SOCKET;
  }

  sts_net_init();
  if (sts_net_open_socket(&server, NULL, "4040") < 0) panic(sts_net_get_last_error());
  sts_net_init_socket_set(&set);
  if (sts_net_add_socket_to_set(&server, &set) < 0) panic(sts_net_get_last_error());

  while(1) {
    puts("Waiting...");
    if (sts_net_check_socket_set(&set, 0.5) < 0) panic(sts_net_get_last_error());
    // check server
    if (server.ready) {
      for (i = 0; i < STS_NET_SET_SOCKETS; ++i) {
        if (clients[i].fd == INVALID_SOCKET) {
          if (sts_net_accept_socket(&server, &clients[i]) < 0) panic(sts_net_get_last_error());
          if (sts_net_add_socket_to_set(&clients[i], &set) < 0) panic(sts_net_get_last_error());
          puts("Client connected!");
          break;
        }
      }
    }

    // check clients
    for (i = 0; i < STS_NET_SET_SOCKETS; ++i) {
      if (clients[i].ready) {
        memset(buffer, 0, sizeof(buffer));
        bytes = sts_net_recv(&clients[i], buffer, sizeof(buffer) - 1);
        if (bytes <= 0) {
          if (sts_net_remove_socket_from_set(&clients[i], &set) < 0) panic(sts_net_get_last_error());
          sts_net_close_socket(&clients[i]);
          puts("Client disconnected");
        } else {
          // broadcast
          for (j = 0; j < STS_NET_SET_SOCKETS; ++j) {
            if (clients[j].fd != INVALID_SOCKET) {
              if (sts_net_send(&clients[j], buffer, bytes) < 0) panic(sts_net_get_last_error());
            }
          }
          printf("Broadcast: %s\n", buffer);
        }
      }
    }
  }

  sts_net_shutdown();
  return 0;
}