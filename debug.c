#include "data_structures.h"
#include <stdio.h>
#include <time.h>

void request_dissect(char *request) {
  time_t request_time = time(NULL);
  struct tm tm = *localtime(&request_time);

  fprintf(stdout, "Request accepted @ %d-%02d-%02d %02d:%02d:%02d \n",
          tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min,
          tm.tm_sec);

  fprintf("Raw data: %s \n", request);
}
