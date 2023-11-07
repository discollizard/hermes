#ifndef WEBFUNCTIONS_H_
#define WEBFUNCTIONS_H_

#include "debug.h"
#include "params.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int open_socket_or_die();
void set_sock_opts_or_die(int socket_file_descriptor);
void get_client_address_or_die(char *ipv4_destination_pointer,
                               struct sockaddr_in *client_sock_addr,
                               int max_buffer_size);
void bind_socket_or_die(int socket_file_descriptor,
                        struct sockaddr_in *sock_struct);
char *parse_url_file_request(char *request);
void handle_connection(int client_fd);

typedef struct {
  char name[MAX_HTTP_HEADER_NAME_LEN];   // okay, this could have any type, but
                                         // http parsing only uses string
  char value[MAX_HTTP_HEADER_VALUE_LEN]; // arbitrary
} cons;

typedef struct {
  char status_code[8];            // options length + null terminator
  char path[MAXPATHLEN];          // arbitrary
  char http_ver[4];               // 1.1 length + null terminator
  cons headers[MAX_HTTP_HEADERS]; // arbitrary
} http_req;

#endif
