#ifndef WEBFUNCTIONS_H_
#define WEBFUNCTIONS_H_

#include "params.h"

int open_socket_or_die();

void set_sock_opts(int socket_file_descriptor);

void bind_socket_or_die(int socket_file_descriptor, struct sockaddr_in* sock_struct);

typedef struct {
  char name[MAX_HTTP_HEADER_NAME_LEN]; //okay, this could have any type, but http parsing only uses string
  char value[MAX_HTTP_HEADER_VALUE_LEN]; //arbitrary
} cons;

typedef struct {
  char status_code[8]; //options length + null terminator
  char path[MAXPATHLEN]; //arbitrary
  char http_ver[4]; // 1.1 length + null terminator
  cons headers[MAX_HTTP_HEADERS]; //arbitrary
} http_req;

#endif
