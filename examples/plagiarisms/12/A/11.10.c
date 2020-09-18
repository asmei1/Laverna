#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main(void)
{
  int spr = 0, err = 0, choice = 0, num = 0, i = 0;

  struct doubly_linked_list_t *dll = dll_create();
  if(!dll){
    printf("Failed to allocate memory");
    return 8;
  }

  while(1){
    printf("Enter operation: ");
    spr = scanf("%d",&choice);
    if(spr!=1){
      printf("Incorrect input");
      dll_clear(dll);
      free(dll);
      return 1;
    }
    if(choice==0) break;
    else if(choice==1){
      printf("Enter liczbe: ");
      spr = scanf("%d", &num);

      if(spr!=1){
        printf("Incorrect input");
        dll_clear(dll);
        free(dll);
        return 1;
      }
      spr = dll_push_back(dll, num);
      if(spr!=0){
        printf("Failed to allocate memory");
        dll_clear(dll);
        free(dll);
        return 8;
      }
    }
    else if(choice==2){
      if(dll_is_empty(dll)==1) printf("List is empty\n");
      else{
        spr = dll_pop_back(dll, &err);
        printf("%d\n", spr);
      }
    }
    else if(choice==3){
      printf("Enter nubmer: ");
      spr = scanf("%d",&num);
      if(spr!=1){
        printf("Incorrect input");
        dll_clear(dll);
        free(dll);
        return 1;
      }
      spr = dll_push_front(dll, num);
      if(spr!=0){
        printf("Failed to allocate memory");
        dll_clear(dll);
        free(dll);
        return 8;
      }
    }
    else if(choice==4){
      if(dll_is_empty(dll)==1) printf("List is empty\n");
      else{
        spr = dll_pop_front(dll, &err);
        printf("%d\n", spr);
      }
    }
    else if(choice==5){
      printf("Enter number: ");
      spr = scanf("%d",&num);
      if(spr!=1){
        printf("Incorrect input");
        dll_clear(dll);
        free(dll);
        return 1;
      }

      printf("Enter index: ");
      spr = scanf("%d", &i);
      if(spr!=1){
        printf("Incorrect input");
        dll_clear(dll);
        free(dll);
        return 1;
      }

      spr = dll_insert(dll, i, num);
      if(spr==2){
        printf("Failed to allocate memory");
        dll_clear(dll);
        free(dll);
        return 8;
      }
      else if(spr==1){
        printf("Index out of range\n");
      }
    }
    else if(choice==6){
      if(dll_is_empty(dll)==1) printf("List is empty\n");
      else{
        printf("Enter index: ");
        spr = scanf("%d", &i);
        if(spr!=1){
          printf("Incorrect input");
          dll_clear(dll);
          free(dll);
          return 1;
        }

        spr = dll_remove(dll, i, &err);
        if(err==1){
          printf("Index out of range\n");
        }
        else printf("%d\n", spr);
      }
    }
    else if(choice==7){
      spr = dll_back(dll, &err);
      if(err==1) 
        printf("List is empty\n");
      else 
        printf("%d\n", spr);
    }
    else if(choice==8){
      spr = dll_front(dll, &err);
      if(err==1) 
        printf("List is empty\n");
      else 
        printf("%d\n", spr);
    }
    else if(choice==9){
      if(dll_is_empty(dll)==1)
        printf("1\n");
      else 
        printf("0\n");
    }
    else if(choice==10){
      spr = dll_size(dll);
      printf("%d\n", spr);
    }
    else if(choice==11){
      dll_clear(dll);
    }
    else if(choice==12){
      if(dll_is_empty(dll)==1) 
        printf("List is empty\n");
      else{
        printf("Enter index: ");
        spr = scanf("%d",&i);
        if(spr!=1){
          printf("Incorrect input");
          dll_clear(dll);
          free(dll);
          return 1;
        }

        spr = dll_at(dll, i, &err);
        if(err==1){
          printf("Index out of range\n");
        }
        else printf("%d\n",spr);
      }
    }
    else if(choice==13){
      if(dll_is_empty(dll)==1) 
        printf("List is empty\n");
      else{
        dll_display(dll);
      }
    }
    else if(choice==14){
      if(dll_is_empty(dll)==1) 
        printf("List is empty\n");
      else{
        dll_display_reverse(dll);
      }
    }
    else{
      printf("Incorrect input data\n");
      continue;
    }
  }
  dll_clear(dll);
  free(dll);

  return 0;
}


