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

/**
 * Note from Otavio R. Piske: this is a modified version of the sts_net library
 * available on https://github.com/kieselsteini/sts/blob/master/sts_net.h.
 *
 * Some differences:
 * - The "packets" API was removed.
 * - The code was separated in multiple files
 * - The comments were modified to Doxygen format
 */


////////////////////////////////////////////////////////////////////////////////
/*
 sts_net.h - v0.07 - public domain
 written 2017 by Sebastian Steinhauer

  VERSION HISTORY
    0.07 (2017-02-24) added checks for a valid socket in every function
                      return 0 for an empty socket set
    0.06 (2017-01-14) fixed warnings when compiling on Windows 64-bit
    0.05 (2017-01-12) added sts_net_is_socket_valid()
                      changed sts_net_send() to const data
    0.04 (2016-05-20) made sts_net_reset_socket public
    0.03 (2016-05-04) fixed timeout in sts_net_check_socket_set
    0.02 (2016-05-03) fixed sts_net_open_socket to work without warnings in Windows
                      removed sts_net_resolve_host and sts_net_address_t
    0.01 (2016-05-01) initial version

  LICENSE
    Public domain. See "unlicense" statement at the end of this file.

  ABOUT
    A simple BSD socket wrapper.

  REMARKS
    The packet API is still work in progress.

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __INCLUDED__STS_NET_H__
#define __INCLUDED__STS_NET_H__

#include <common/gru_portable.h>


#ifndef STS_NET_SET_SOCKETS
// define a bigger default if needed
// this is the maximum amount of sockets you can keep in a socket set
#define STS_NET_SET_SOCKETS   32
#endif // STS_NET_SET_SOCKETS

#ifndef STS_NET_BACKLOG
// amount of waiting connections for a server socket
#define STS_NET_BACKLOG       2
#endif // STS_NET_BACKLOG

#include <string.h>

#ifdef _WIN32
#include <WinSock2.h>
#include <Ws2tcpip.h>
typedef int socklen_t;
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define INVALID_SOCKET    -1
#define SOCKET_ERROR      -1
#define closesocket(fd)   close(fd)
#endif


#ifndef sts__memcpy
#define sts__memcpy     memcpy
#endif // sts__memcpy
#ifndef sts__memset
#define sts__memset     memset
#endif // sts__memset


////////////////////////////////////////////////////////////////////////////////
//
//    Structures
//
typedef struct {
  int   fd;             // socket file descriptor
  int   ready;          // flag if this socket is ready or not
  int   server;         // flag indicating if it is a server socket
} sts_net_socket_t;


typedef struct {
  sts_net_socket_t* sockets[STS_NET_SET_SOCKETS];
} sts_net_set_t;


// REMARK: most functions return 0 on success and -1 on error. You can get a more verbose error message
// from sts_net_get_last_error. Functions which behave differently are the sts_net packet api and sts_net_check_socket_set.


////////////////////////////////////////////////////////////////////////////////
//
//    General API
//

/**
 * Get the last error from sts_net (can be called even before sts_net_init)
 */

gru_export const char* sts_net_get_last_error();

/**
 * Initializes the sts_net library. You have to call this before any other
 * function (except sts_net_get_last_error)
 */

gru_export int sts_net_init();

/**
 * Shutdown the sts_net library.
 */
gru_export void sts_net_shutdown();


////////////////////////////////////////////////////////////////////////////////
//
//    Low-Level Socket API
//


/**
 * Reset a socket (clears the structure). THIS WILL NOT CLOSE the socket.
 * It's meant to "clear" the socket structure.
 */
gru_export void sts_net_reset_socket(sts_net_socket_t* socket);

/**
 * Check if the socket structure contains a "valid" socket.
 * @param socket
 * @return
 */
gru_export int sts_net_is_socket_valid(sts_net_socket_t* socket);

/**
 * Open a (TCP) socket. If you provide "host" sts_net will try to connect to a remove host.
 * Pass NULL for host and you'll have a server socket.
 * @param socket
 * @param host
 * @param service
 * @return
 */
gru_export int sts_net_open_socket(sts_net_socket_t* socket, const char* host, const char* service);

/**
 * Closes the socket.
 * @param socket
 */
gru_export void sts_net_close_socket(sts_net_socket_t* socket);

/**
 * Try to accept a connection from the given server socket.
 * @param listen_socket
 * @param remote_socket
 * @return
 */
gru_export int sts_net_accept_socket(sts_net_socket_t* listen_socket, sts_net_socket_t* remote_socket);

/**
 * Send data to the socket.
 * @param socket
 * @param data
 * @param length
 * @return
 */
gru_export int sts_net_send(sts_net_socket_t* socket, const void* data, int length);

/**
 * Receive data from the socket.
 * @note: this call will block if the socket is not ready (meaning there's no data to receive).
 * @param socket
 * @param data
 * @param length
 * @return
 */
gru_export int sts_net_recv(sts_net_socket_t* socket, void* data, int length);

/**
 * Initializes a socket set.
 * @param set
 */
gru_export void sts_net_init_socket_set(sts_net_set_t* set);

/**
 * Adds a socket to the socket set.
 * @param socket
 * @param set
 * @return
 */
gru_export int sts_net_add_socket_to_set(sts_net_socket_t* socket, sts_net_set_t* set);

/**
 * Remove a socket from the socket set. You have to remove the socket from a set manually.
 * sts_net_close_socket WILL NOT DO THAT!
 * @param socket
 * @param set
 * @return
 */
gru_export int sts_net_remove_socket_from_set(sts_net_socket_t* socket, sts_net_set_t* set);

/**
 * Checks for activity on all sockets in the given socket set. If you want to peek for
 * events pass 0.0f to the timeout. All sockets will have set the ready property to
 * non-zero if you can read data from it, or can accept connections.
 * @return -1  on errors, 0  if there was no activity, >0  amount of sockets with activity
 */
gru_export int sts_net_check_socket_set(sts_net_set_t* set, const float timeout);

#endif // __INCLUDED__STS_NET_H__