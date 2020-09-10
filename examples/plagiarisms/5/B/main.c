#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main(void) {
  char *res;
  int err;

  char *expr = (char*)malloc(sizeof(char)*501);
  if(!expr){
    printf("Failed to allocate memory");
    return 8;
  }

  printf("Podaj pierwsza rownanie: ");
  scanf("%500s", expr);

  while(getchar() != '\n');


  if(!!validate_expression(expr)){
    printf("Incorrect input");
    free(expr);
    return 1;
  }

  err = calculate(expr, &res);

  if(err == 3){
    printf("Failed to allocate memory");
    free(expr);
    return 8;
  }

  printf("%s", res);

  free(res);
  free(expr);

  return 0;
}
