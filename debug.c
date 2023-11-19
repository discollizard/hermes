#include "params.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void pstring(char *string) {
  printf("\n\n -= DEBUG STRING =-");
  if (string == NULL) {
    printf("\n STRING IS NULL\n");
  } else {
    printf("\n (%p) %s - %d chars long\n", &string, string, strlen(string));
  }

  printf("-= END DEBUG STRING =- \n\n");
}
