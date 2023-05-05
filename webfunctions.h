#ifndef WEBFUNCTIONS_H_
#define WEBFUNCTIONS_H_

int open_socket_or_die();

void set_sock_opts(int socket_file_descriptor);

void bind_socket_or_die(int socket_file_descriptor, struct sockaddr_in* sock_struct);

#endif
