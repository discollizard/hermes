#include "webfunctions.h"
#include "params.h"

int open_socket_or_die() {

  int sockfd;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0) {
    perror("Failed to create socket");
    exit(EXIT_FAILURE);
  }

  return sockfd;
}

void set_sock_opts_or_die(int socket_file_descriptor) {

  int reuse_address_and_port = 1;

  if (setsockopt(socket_file_descriptor, SOL_SOCKET,
                 SO_REUSEADDR | SO_REUSEPORT, &reuse_address_and_port,
                 sizeof(reuse_address_and_port)) < 0) {
    perror("Failed to set socket options");
    close(socket_file_descriptor);
    exit(EXIT_FAILURE);
  }
}

void bind_socket_or_die(int socket_file_descriptor,
                        struct sockaddr_in *sock_struct) {

  printf("%p", sock_struct);
  if (bind(socket_file_descriptor, (struct sockaddr *)sock_struct,
           sizeof(*sock_struct)) < 0) {
    perror("Failed to bind socket");
    close(socket_file_descriptor);
    exit(EXIT_FAILURE);
  }
}

void get_client_address_or_die(char *ipv4_destination_pointer,
                               struct sockaddr_in *client_sock_addr,
                               int max_buffer_size) {
  const char *dst_ptr;
  dst_ptr = inet_ntop(AF_INET, &(client_sock_addr->sin_addr),
                      ipv4_destination_pointer, max_buffer_size);
  if (dst_ptr == NULL) {
    perror("Failed to get client address: ");
  }
}

char *parse_url_file_request(char *request) {
  char *file_name;
  FILE *file;

  file_name = (char *)malloc(sizeof(char) * MAXPATHLEN + 1);

  /* printf("Method: %s\n", strtok(request, " ")); */

  file_name = strtok(NULL, " ");

  // log error if file path is longer than 512 bytes
  if (strlen(file_name) > MAXPATHLEN) {
    free(file_name);
    return "-1";
  }

  /* printf("Path: %s", file_name); */

  // TODO: PASS THE REQUEST BODY TO THE HANDLE CONNECTION
  // FUNCTION AND PUT THE FILE CONTENTS IN THE REQUEST BODY
  if (strcmp(file_name, "/")) {
    file = fopen("index.html", "r");

    if (file == NULL) {
      free(file_name);
      return "-2";
    }
  }

  return file_name;
}

void handle_connection(int client_fd) {
  char line_buffer[LINE_BUFFER_SIZE];
  int read_result;

  memset(line_buffer, 0, LINE_BUFFER_SIZE - 1);

  while ((read_result = read(client_fd, line_buffer, LINE_BUFFER_SIZE - 1)) >
         0) {
    // could log this in a file later
    /* DEBUG STUFF */
    request_dissect((char *)&line_buffer);
    /* DEBUG STUFF */
    /* parse_url_file_request((char *)line_buffer); */
    /* if () */

    fprintf(stdout, "\n%s\n", line_buffer);
    fflush(stdout);

    if (line_buffer[strlen(line_buffer) - 1] == '\n') {
      break;
    }

    memset(line_buffer, 0, LINE_BUFFER_SIZE - 1);
  }
}
