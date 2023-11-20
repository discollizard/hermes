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

const char *get_mime_type(const char *file_extension) {
  if (strcmp(file_extension, "jpg") == 0 ||
      strcmp(file_extension, "jpeg") == 0) {
    return "image/jpeg";
  } else if (strcmp(file_extension, "html") == 0) {
    return "text/html";
  } else if (strcmp(file_extension, "css") == 0) {
    return "text/css";
  } else if (strcmp(file_extension, "png") == 0) {
    return "image/png";
  } else if (strcmp(file_extension, "gif") == 0) {
    return "image/gif";
  } else if (strcmp(file_extension, "pdf") == 0) {
    return "application/pdf";
  } else if (strcmp(file_extension, "doc") == 0 ||
             strcmp(file_extension, "docx") == 0) {
    return "application/msword";
  } else if (strcmp(file_extension, "xls") == 0 ||
             strcmp(file_extension, "xlsx") == 0) {
    return "application/vnd.ms-excel";
  } else if (strcmp(file_extension, "ppt") == 0 ||
             strcmp(file_extension, "pptx") == 0) {
    return "application/vnd.ms-powerpoint";
  } else if (strcmp(file_extension, "mp3") == 0) {
    return "audio/mpeg";
  } else if (strcmp(file_extension, "mp4") == 0) {
    return "video/mp4";
  } else if (strcmp(file_extension, "avi") == 0) {
    return "video/x-msvideo";
  } else if (strcmp(file_extension, "txt") == 0) {
    return "text/plain";
  } else {
    // Add more file extensions and corresponding mime types as needed
    return "application/octet-stream"; // Default mime type for unknown file
                                       // types
  }
}

void build_http_response(char *file_name, const char *file_ext, char *response,
                         size_t *response_len) {
  char *header = (char *)malloc(BUFFER_SIZE * sizeof(char));
  const char *mime_type = get_mime_type(file_ext);

  // 404 if file doesnt exist
  int file_fd = open(file_name, O_RDONLY);
  if (file_fd == -1 && file_name[strlen(file_name) - 1] != '/') {
    snprintf(response, BUFFER_SIZE,
             "HTTP/1.1 404 Not Found\r\n"
             "Content-type: text/plain\r\n"
             "\r\n"
             "404 Not Found");
    *response_len = strlen(response);
    return;
  } else if (file_name[strlen(file_name) - 1] == '/') {
    strcat(file_name, "index.html");
    file_fd = open(file_name, O_RDONLY);
    if (file_fd == -1) {
      snprintf(response, BUFFER_SIZE,
               "HTTP/1.1 404 Not Found\r\n"
               "Content-type: text/plain\r\n"
               "\r\n"
               "404 Not Found");
      *response_len = strlen(response);
      return;
    }
    mime_type = get_mime_type("html");
  }

  snprintf(header, BUFFER_SIZE,
           "HTTP/1.1 200 OK\r\n"
           "Content-Type: %s\r\n"
           "\r\n",
           mime_type);

  struct stat file_stat;
  fstat(file_fd, &file_stat);
  off_t file_size = file_stat.st_size;

  *response_len = 0;
  memcpy(response, header, strlen(header));
  *response_len += strlen(header);

  ssize_t bytes_read;
  while ((bytes_read = read(file_fd, response + *response_len,
                            BUFFER_SIZE - *response_len)) > 0) {
    *response_len += bytes_read;
  }
  free(header);
  close(file_fd);
}

char *url_decode(char *url_encoded_file_name) {
  char *last_half_of_path =
      malloc((strlen(url_encoded_file_name) + 1) * sizeof(char));
  ssize_t file_name_length = strlen(url_encoded_file_name);

  for (int i = 0; i < file_name_length; i++) {
    if (url_encoded_file_name[i] == '%') {
      if (url_encoded_file_name[i + 1] == '2') {
        if (url_encoded_file_name[i + 2] == '0') {
          decode_url_param(url_encoded_file_name, "%20", ' ', last_half_of_path,
                           i, file_name_length);
        } else if (url_encoded_file_name[i + 2] == '1') {
          decode_url_param(url_encoded_file_name, "%21", '!', last_half_of_path,
                           i, file_name_length);
        } else if (url_encoded_file_name[i + 2] == '2') {
          decode_url_param(url_encoded_file_name, "%22", '"', last_half_of_path,
                           i, file_name_length);
        } else if (url_encoded_file_name[i + 2] == '3') {
          decode_url_param(url_encoded_file_name, "%23", '#', last_half_of_path,
                           i, file_name_length);
        } else if (url_encoded_file_name[i + 2] == '4') {
          decode_url_param(url_encoded_file_name, "%24", '$', last_half_of_path,
                           i, file_name_length);
        } else if (url_encoded_file_name[i + 2] == '5') {
          decode_url_param(url_encoded_file_name, "%25", '%', last_half_of_path,
                           i, file_name_length);
        } else if (url_encoded_file_name[i + 2] == '6') {
          decode_url_param(url_encoded_file_name, "%26", '&', last_half_of_path,
                           i, file_name_length);
        } else if (url_encoded_file_name[i + 2] == '7') {
          decode_url_param(url_encoded_file_name, "%27", '\'',
                           last_half_of_path, i, file_name_length);
        } else if (url_encoded_file_name[i + 2] == '8') {
          decode_url_param(url_encoded_file_name, "%28", '(', last_half_of_path,
                           i, file_name_length);
        } else if (url_encoded_file_name[i + 2] == '9') {
          decode_url_param(url_encoded_file_name, "%29", ')', last_half_of_path,
                           i, file_name_length);
        } else if (url_encoded_file_name[i + 2] == 'A') {
          decode_url_param(url_encoded_file_name, "%2A", '*', last_half_of_path,
                           i, file_name_length);
        } else if (url_encoded_file_name[i + 2] == 'B') {
          decode_url_param(url_encoded_file_name, "%2B", '+', last_half_of_path,
                           i, file_name_length);
        } else if (url_encoded_file_name[i + 2] == 'C') {
          decode_url_param(url_encoded_file_name, "%2C", ',', last_half_of_path,
                           i, file_name_length);
        } else if (url_encoded_file_name[i + 2] == 'E') {
          decode_url_param(url_encoded_file_name, "%2E", '.', last_half_of_path,
                           i, file_name_length);
        } else if (url_encoded_file_name[i + 2] == 'F') {
          decode_url_param(url_encoded_file_name, "%2F", '/', last_half_of_path,
                           i, file_name_length);
        }
      }
    }
  }
  free(last_half_of_path);
  return url_encoded_file_name;
}

void decode_url_param(char *file_name, const char *url_code,
                      const char char_to_transform, char *last_half_of_path,
                      int index, ssize_t file_name_length) {
  file_name[index] = char_to_transform;
  int name_counter = 0;
  for (int j = index + 3; j < file_name_length; j++) {
    last_half_of_path[name_counter] = file_name[j];
    name_counter++;
  }

  file_name[index + 1] = '\0';
  strcat(file_name, (const char *)last_half_of_path);
}

const char *get_file_extension(const char *url) {
  const char *slash = strrchr(url, '/');
  const char *filename = (slash != NULL) ? slash + 1 : url;
  const char *dot = strrchr(filename, '.');

  if (dot && dot != filename) {
    return dot + 1; // Return the string after the dot
  }

  return ""; // Return an empty string if no extension found
}

uint64_t func_hash(const char *key, size_t keylen) {
  int toReturn = 0;

  for (int i = 0; i < keylen; i++) {
    toReturn += key[i];
  }
  return toReturn;
}

void parse_query_params(char *request) {
  uint64_t (*functionPtr)(const char *, size_t keylen);
  functionPtr = &func_hash;

  hash_table *params = init_hash_table(20, functionPtr);
  char *key = strtok(request, "=");
  char *value = strtok(NULL, "&");
  hash_table_insert(params, key, value);
  while (value != NULL) {
    key = strtok(NULL, "=");
    value = strtok(NULL, "&");
    hash_table_insert(params, key, value);
  }
  hash_table_print(params);
}

void handle_connection(void *client_fd) {
  int client_id = *((int *)client_fd);
  char *buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));

  ssize_t bytes_received = recv(client_id, buffer, BUFFER_SIZE, 0);
  if (bytes_received < 0) {
    printf("Error while receiving bytes: %d", errno);
    exit(errno);
  }
  if (bytes_received > 0) {
    // GET requests
    regex_t regex_get;
    regcomp(&regex_get, "^GET /([^ ]*) HTTP/1", REG_EXTENDED);
    regmatch_t matches[2];

    printf("%s", buffer);

    if (regexec(&regex_get, buffer, 2, matches, 0) == 0) {
      // extract filename from request and decode URL
      buffer[matches[1].rm_eo] = '\0';
      char *url_encoded_file_name = buffer + matches[1].rm_so;
      char *file_name =
          malloc(sizeof(char) * (strlen(url_encoded_file_name) + 1));
      if (strstr(url_encoded_file_name, "?") != NULL) {
        file_name = url_decode(strtok(url_encoded_file_name, "?"));
        parse_query_params(strtok(NULL, ""));
      } else {
        file_name = url_decode(url_encoded_file_name);
      }

      char file_ext[32];
      strcpy(file_ext, get_file_extension(file_name));

      char *response = (char *)malloc(BUFFER_SIZE * 2 * sizeof(char));
      size_t response_len;

      build_http_response(file_name, file_ext, response, &response_len);

      send(client_id, response, response_len, 0);

      printf("%s", response);
      free(response);
      // free(file_name);
    }
    regfree(&regex_get);
  }
  close(client_id);
  free(buffer);
}
