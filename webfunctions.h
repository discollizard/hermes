#ifndef WEBFUNCTIONS_H_
#define WEBFUNCTIONS_H_

#include "debug.h"
#include "params.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int open_socket_or_die();
void set_sock_opts_or_die(int socket_file_descriptor);
void get_client_address_or_die(char *ipv4_destination_pointer,
                               struct sockaddr_in *client_sock_addr,
                               int max_buffer_size);
void bind_socket_or_die(int socket_file_descriptor,
                        struct sockaddr_in *sock_struct);
void handle_connection(void* client_fd);

const char* get_mime_type(const char* file_extension);
char* url_decode(char* url_encoded_file_name);
void decode_url_param(char* file_name, const char* url_code, const char char_to_transform, char* last_half_of_path, int index, ssize_t file_name_length);
const char* get_file_extension(const char* url);
void build_http_response(const char* file_name, const char* file_ext, char* response, size_t* response_len);

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
