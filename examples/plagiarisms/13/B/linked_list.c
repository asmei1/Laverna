#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "linked_list.h"
#include "tested_declarations.h"
#include "rdebug.h"

int ll_push_back(struct linked_list_t* ll, char *value){
  if(!ll) return 1;

  struct node_t *pNode = (struct node_t*)malloc(sizeof(struct node_t));
  if(!pNode) return 2;

  pNode->data = (char*)calloc(strlen(value)+1, sizeof(char));
  if(!pNode->data){
    free(pNode);
    return 2;
  }

  if(!ll->tail){
    strcpy(pNode->data, value);
    pNode->next = NULL;
    ll->head = pNode;
    ll->tail = pNode;
  }
  else{
    strcpy(pNode->data, value);
    pNode->next = NULL;
    ll->tail->next = pNode;
    ll->tail = pNode;
  }

  return 0;
}

int ll_push_front(struct linked_list_t* ll, char *value){
  if(!ll) return 1;

  struct node_t *pNode = (struct node_t*)malloc(sizeof(struct node_t));
  if(!pNode) return 2;

  pNode->data = (char*)calloc(strlen(value)+1, sizeof(char));
  if(!pNode->data){
    free(pNode);
    return 2;
  }

  if(!ll->head){
    strcpy(pNode->data, value);
    pNode->next = NULL;
    ll->head = pNode;
    ll->tail = pNode;
  }
  else{
    strcpy(pNode->data, value);
    pNode->next = ll->head;
    ll->head = pNode;
  }

  return 0;
}

int ll_size(const struct linked_list_t* ll){
  if(!ll) return -1;
  if(!ll->head) return 0;

  struct node_t *pHead = ll->head;
  int ok = 0;
  while(pHead){
    struct node_t *tmp;
    tmp = pHead->next;
    ok++;
    pHead = tmp;
  }

  return ok;
}

int ll_is_empty(const struct linked_list_t* ll){
  if(!ll) 
    return -1;
  else if(!ll->head) 
    return 1;
  return 0;
}

int ll_insert(struct linked_list_t* ll, unsigned int index, char *value){
  if(!ll || (int)index<0) return 1;
  int size = ll_size(ll), spr;
  if((int)index>size) return 1;

  if((int)index==0){
    spr = ll_push_front(ll, value);
    if(spr!=0) return 2;
    return 0;
  }

  if((int)index==size){
    spr = ll_push_back(ll, value);
    if(spr!=0) return 2;
    return 0;
  }

  struct node_t *pNode = (struct node_t*)malloc(sizeof(struct node_t));
  if(!pNode) return 2;

  pNode->data = (char*)calloc(strlen(value)+1, sizeof(char));
  if(!pNode->data){
    free(pNode);
    return 2;
  }

  strcpy(pNode->data, value);

  struct node_t *tmp = ll->head;

  for(int i=1; i<(int)index; i++){
    tmp = tmp->next;
  }

  pNode->next = tmp->next;
  tmp->next = pNode;

  return 0;
}

void ll_clear(struct linked_list_t* ll){
  if(!ll || !ll->head || !ll->tail) return;

  struct node_t *pHead = ll->head;
  while(pHead){
    struct node_t *tmp;
    tmp = pHead->next;
    free(pHead->data);
    free(pHead);
    pHead = tmp;
  }

  ll->head = NULL;
  ll->tail = NULL;
}

void ll_display(const struct linked_list_t* ll){
  if(!ll || !ll->head || !ll->tail) return;

  struct node_t *tmp;
  tmp = ll->head;

  while(tmp){
    printf("%s ", tmp->data);
    tmp = tmp->next;
  }
  printf("\n");
}

int ll_insert_words(struct linked_list_t* ll, int N, ...){
  if(!ll || N<1) return -1;
  int i = 0, j = 0, size = 0, spr = 0, ok=0, n = N;
  char *tab = 0;

  if(ll->head){
    spr = ll_is_sorted_ascending(ll);
    if(spr!=1) return -1;
  }

  va_list valist;
  va_start(valist, N);

  for(i=0; i<n; i++){
    size = ll_size(ll);
    tab = va_arg(valist, char*);
    if(!ll->head){
      spr = ll_push_front(ll, tab);
      if(spr==2){
        va_end(valist);
        return ok;
      }
      ok++;
    }
    else{
      struct node_t *tmp;
      tmp = ll->head;
      for(j=0; j<size; j++){
        if(strcmp(tab,tmp->data)<0){
          spr = ll_insert(ll,j,tab);
          if(spr==2){
            va_end(valist);
            return ok;
          }
          ok++;
          break;
        }
        tmp = tmp->next;
      }

      if(j==size){
        spr = ll_push_back(ll,tab);
        if(spr==2){
          va_end(valist);
          return ok;
        }
        ok++;
      }
    }
    
    spr = ll_is_sorted_ascending(ll);
    if(spr!=1){
      va_end(valist);
      return -1;
    }
  }

  va_end(valist);
  return ok;
}
int ll_is_sorted_ascending(const struct linked_list_t* ll){
  if(!ll || !ll->head) return -1;

  struct node_t *tmp;
  tmp = ll->head;

  while(tmp->next){
    if(strcmp(tmp->data, tmp->next->data)>0) return 0;
    tmp = tmp->next;
  }

  return 1;
}

struct linked_list_t* ll_create(){
  struct linked_list_t *ll = (struct linked_list_t*)malloc(sizeof(struct linked_list_t));
  if(!ll) return NULL;

  ll->head = NULL;
  ll->tail = NULL;

  return ll;
}

