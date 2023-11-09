#ifndef PARAMS_H
#define PARAMS_H

#define PORT 80
#define LINE_BUFFER_SIZE 4096
#define MAXADDRLEN 128
#define MAXPATHLEN 512
#define MAX_HTTP_HEADER_NAME_LEN 2048
#define MAX_HTTP_HEADER_VALUE_LEN 2048
#define MAX_HTTP_HEADERS 100
#define MAX_HTTP_BODY_NAME_LEN 2048
#define MAX_HTTP_BODY_VALUE_LEN 2048
#define MAX_HTTP_BODY_COUNT 100

typedef struct {
    char key[MAX_HTTP_HEADER_NAME_LEN];
    char value[MAX_HTTP_HEADER_VALUE_LEN];
} headerPair;

typedef struct {
    char key[MAX_HTTP_BODY_NAME_LEN];
    char value[MAX_HTTP_BODY_VALUE_LEN];
} bodyPair;

typedef struct {
    char host[MAXADDRLEN];
    char path[MAXPATHLEN];
    char version[10];
    char method[8];
    headerPair headers[MAX_HTTP_HEADERS];
    int headerCount;
    bodyPair body[MAX_HTTP_BODY_COUNT];
} httpRequest;

#endif
