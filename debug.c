#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "params.h"

void get_metadata(httpRequest** requestStruct, char* httpHead){
  strcpy((*requestStruct)->method, strtok(httpHead, " "));
  //checking for post body
    strcpy((*requestStruct)->path, strtok(NULL, " "));
    strcpy((*requestStruct)->version, strtok(NULL, " "));
}

 httpRequest* request_dissect(char *requestText) {
  time_t request_time = time(NULL);
  struct tm tm = *localtime(&request_time);
  char *token;
  char* requestMetadata;
  httpRequest *request = malloc(sizeof(httpRequest));

  fprintf(stdout, "Request accepted @ %d-%02d-%02d %02d:%02d:%02d \n",
          tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min,
          tm.tm_sec);

  fprintf(stdout, "Raw data: %s \n", requestText);

  get_metadata(&request, strtok(requestText, "\n"));
  fprintf(stdout, "Method: %s \n", request->method);
  fprintf(stdout, "HTTP Version: %s \n", request->version);
  fprintf(stdout, "Path: %s \n", request->path);

  //figure out the rest later

  return request;
}
