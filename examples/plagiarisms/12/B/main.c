#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "doubly_linked_list.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main(void)
{
  struct doubly_linked_list_t *dll = dll_create();
  if (!dll)
  {
    printf("Failed to allocate memory");
    return 8;
  }
  int spr, err_code, what = 0, x, i;

  do
  {
    printf("Co chcesz zrobic?: ");
    spr = scanf("%d", &what);

    if (spr!=1)
    {
      printf("Incorrect input");
      dll_clear(dll);
      free(dll);
      return 1;
    }

    if (what==0) break;
    else if (what==1)
    {
      printf("Podaj liczbe: ");
      spr = scanf("%d", &x);

      if (spr!=1)
      {
        printf("Incorrect input");
        dll_clear(dll);
        free(dll);
        return 1;
      }
      spr = dll_push_back(dll, x);
      if (spr!=0)
      {
        printf("Failed to allocate memory");
        dll_clear(dll);
        free(dll);
        return 8;
      }
    }
    else if (what==2)
    {
      if (dll_is_empty(dll)==1) printf("List is empty\n");
      else
      {
        spr = dll_pop_back(dll, &err_code);
        printf("%d\n", spr);
      }
    }
    else if (what==3)
    {
      printf("Podaj liczbe: ");
      spr = scanf("%d", &x);

      if (spr!=1)
      {
        printf("Incorrect input");
        dll_clear(dll);
        free(dll);
        return 1;
      }
      spr = dll_push_front(dll, x);
      if (spr!=0)
      {
        printf("Failed to allocate memory");
        dll_clear(dll);
        free(dll);
        return 8;
      }
    }
    else if (what==4)
    {
      if (dll_is_empty(dll)==1) printf("List is empty\n");
      else
      {
        spr = dll_pop_front(dll, &err_code);
        printf("%d\n", spr);
      }
    }
    else if (what==5)
    {
      printf("Podaj liczbe: ");
      spr = scanf("%d", &x);

      if (spr!=1)
      {
        printf("Incorrect input");
        dll_clear(dll);
        free(dll);
        return 1;
      }

      printf("Podaj index: ");
      spr = scanf("%d", &i);
      if (spr!=1)
      {
        printf("Incorrect input");
        dll_clear(dll);
        free(dll);
        return 1;
      }

      spr = dll_insert(dll, i, x);
      if (spr==2)
      {
        printf("Failed to allocate memory");
        dll_clear(dll);
        free(dll);
        return 8;
      }
      else if (spr==1)
      {
        printf("Index out of range\n");
      }
    }
    else if (what==6)
    {
      if (dll_is_empty(dll)==1) printf("List is empty\n");
      else
      {
        printf("Podaj index: ");
        spr = scanf("%d", &i);

        if (spr!=1)
        {
          printf("Incorrect input");
          dll_clear(dll);
          free(dll);
          return 1;
        }

        spr = dll_remove(dll, i, &err_code);
        if (err_code==1)
        {
          printf("Index out of range\n");
        }
        else printf("%d\n", spr);
      }
    }
    else if (what==7)
    {
      spr = dll_back(dll, &err_code);
      if (err_code==1) printf("List is empty\n");
      else printf("%d\n", spr);
    }
    else if (what==8)
    {
      spr = dll_front(dll, &err_code);
      if (err_code==1) printf("List is empty\n");
      else printf("%d\n", spr);
    }
    else if (what==9)
    {
      if (dll_is_empty(dll)==1) printf("1\n");
      else printf("0\n");
    }
    else if (what==10)
    {
      spr = dll_size(dll);
      printf("%d\n", spr);
    }
    else if (what==11)
    {
      dll_clear(dll);
    }
    else if (what==12)
    {
      if (dll_is_empty(dll)==1) printf("List is empty\n");
      else
      {
        printf("Podaj index: ");
        spr = scanf("%d", &i);

        if (spr!=1)
        {
          printf("Incorrect input");
          dll_clear(dll);
          free(dll);
          return 1;
        }

        spr = dll_at(dll, i, &err_code);
        if (err_code==1)
        {
          printf("Index out of range\n");
        }
        else printf("%d\n", spr);
      }
    }
    else if (what==13)
    {
      if (dll_is_empty(dll)==1) printf("List is empty\n");
      else
      {
        dll_display(dll);
      }
    }
    else if (what==14)
    {
      if (dll_is_empty(dll)==1) printf("List is empty\n");
      else
      {
        dll_display_reverse(dll);
      }
    }
    else
    {
      printf("Incorrect input data\n");
      continue;
    }
  } while (1);
  dll_clear(dll);
  free(dll);

  return 0;
}


