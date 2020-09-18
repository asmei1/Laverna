#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include "linked_list.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main(int argc, char **argv)
{
  int N = argc;
  if (N<2)
  {
    printf("Not enough arguments");
    return 9;
  }

  struct linked_list_t *ll = ll_create();
  if (!ll)
  {
    printf("Failed to allocate memory");
    return 8;
  }

  for (int i=1; i<N; i++)
  {
    int spr = ll_insert_words(ll, 1, *(argv+i));
    if (spr!=1)
    {
      printf("Failed to allocate memory");
      ll_clear(ll);
      free(ll);
      return 8;
    }
  }
  if (ll_is_empty(ll)==0) ll_display(ll);
  ll_clear(ll);
  free(ll);

  return 0;
}


