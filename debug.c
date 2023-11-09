#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "params.h"

void get_method(httpRequest** requestStruct, char* httpHead){
  strcpy((*requestStruct)->method, strtok(httpHead, " "));
  //checking for post body
    strcpy((*requestStruct)->path, strtok(NULL, " "));
    strcpy((*requestStruct)->version, strtok(NULL, " "));
}

void request_dissect(char *requestText) {
  time_t request_time = time(NULL);
  struct tm tm = *localtime(&request_time);
  char* headerKVPair;
  httpRequest *request = malloc(sizeof(httpRequest));

  fprintf(stdout, "Request accepted @ %d-%02d-%02d %02d:%02d:%02d \n",
          tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min,
          tm.tm_sec);

  fprintf(stdout, "Raw data: %s \n", requestText);

  //headers
  get_method(&request, strtok(requestText, "\n"));
  fprintf(stdout, "\n\n Method: %s\n", request->method);
  fprintf(stdout, "Path: %s\n", request->path);
  fprintf(stdout, "HTTP version: %s\n", request->version);

  fprintf(stdout, "\n\n Headers: \n");
  while(headerKVPair = strtok(NULL, "\n")){
    fprintf(stdout, " %s\n", headerKVPair);
  }

  free(request);
}

