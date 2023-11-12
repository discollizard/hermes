#include "debug.h"
#include "params.h"
#include "webfunctions.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {

  int server_fd, client_fd, line;
  struct sockaddr_in address;

  server_fd = open_socket_or_die();

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = htonl(INADDR_ANY);
  address.sin_port = htons(PORT);

  // ok, if this function fails, should the program just die?
  // it's not like it won't work, it just wont reuse addresses nor ports
  //
  // maybe log the occurence and move on? idk, TODO
  //

  set_sock_opts_or_die(server_fd);

  bind_socket_or_die(server_fd, &address);

  printf("Listening on port %d...", PORT);

  if (listen(server_fd, 1024) < 0) {
    perror("Error while listening to incoming connections");
    exit(EXIT_FAILURE);
  }

  for (;;) {

        struct sockaddr_in client_addr;
    socklen_t client_address_len;
    char client_address_ipv4[MAXADDRLEN - 1];

    client_fd =
        accept(server_fd, (struct sockaddr *)&client_addr, &client_address_len);

    get_client_address_or_die(client_address_ipv4, &client_addr, MAXADDRLEN);

    printf("Client address: %s\n", client_address_ipv4);

    if (client_fd < 0) {
      perror("Error while accepting incoming connection");
      close(server_fd);
      exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Connection accepted\n server_fd: %d, client_fd: %d\n", server_fd, client_fd);

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, handle_connection, (void *)&client_fd);
    pthread_detach(thread_id);

    if (line < 0) {
      perror("Error while reading from socket");
      close(server_fd);
      exit(EXIT_FAILURE);
    }

  }

  return 0;

}
