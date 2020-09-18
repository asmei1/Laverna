#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "doubly_linked_list.h"
#include "tested_declarations.h"
#include "rdebug.h"

struct doubly_linked_list_t* dll_create(){
  struct doubly_linked_list_t *dll = (struct doubly_linked_list_t*)malloc(sizeof(struct doubly_linked_list_t));
  if (!dll) return NULL;

  dll->head = NULL;
  dll->tail = NULL;

  return dll;
}

int dll_push_back(struct doubly_linked_list_t* dll, int value){
  if(!dll) return 1;

  struct node_t *pNode = (struct node_t*)malloc(sizeof(struct node_t));
  if(!pNode) return 2;

  if(!dll->tail){
    pNode->data = value;
    pNode->next = NULL;
    pNode->prev = NULL;
    dll->head = pNode;
    dll->tail = pNode;
  }
  else{
    pNode->data = value;
    dll->tail->next = pNode;
    pNode->prev = dll->tail;
    dll->tail = pNode;
    dll->tail->next = NULL;
  }

  return 0;
}

int dll_push_front(struct doubly_linked_list_t* dll, int value){
  if(!dll) return 1;

  struct node_t *pNode = (struct node_t*)malloc(sizeof(struct node_t));
  if(!pNode) return 2;

  if(!dll->head){
    pNode->data = value;
    pNode->next = NULL;
    pNode->prev = NULL;
    dll->head = pNode;
    dll->tail = pNode;
  }
  else{
    pNode->data = value;
    pNode->next = dll->head;
    dll->head->prev = pNode;
    dll->head = pNode;
    dll->head->prev = NULL;
  }

  return 0;
}

int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code){
  if(!dll || !dll->head || !dll->tail){
    if(err_code) *err_code = 1;
    return -1;
  }

  int res = dll->tail->data;
  struct node_t *temp = dll->head;
  if(temp->next){
    free(dll->tail);
    while (temp->next!=dll->tail) 
      temp = temp->next;
    dll->tail = temp;
    dll->tail->next = NULL;
  }
  else{
    temp = dll->tail;
    free(temp);
    dll->head = NULL;
    dll->tail = NULL;
  }

  if(err_code) *err_code = 0;

  return res;
}

int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code){
  if(!dll || !dll->head || !dll->tail){
    if(err_code) *err_code = 1;
    return -1;
  }

  int res = dll->head->data;
  struct node_t *temp = dll->head;
  if(temp->next){
    free(temp);
    dll->head = dll->head->next;
    dll->head->prev = NULL;
  }
  else{
    dll->tail = NULL;
    free(temp);
    dll->head = NULL;
  }

  if(err_code) *err_code = 0;

  return res;
}

int dll_back(const struct doubly_linked_list_t* dll, int *err_code){
  if(!dll || !dll->tail){
    if(err_code) *err_code = 1;
    return -1;
  }

  if(err_code) *err_code = 0;

  return dll->tail->data;
}

int dll_front(const struct doubly_linked_list_t* dll, int *err_code){
  if(!dll || !dll->head){
    if(err_code) *err_code = 1;
    return -1;
  }

  if(err_code) *err_code = 0;

  return dll->head->data;
}

struct node_t* dll_end(struct doubly_linked_list_t* dll){
  if(!dll || !dll->head) return NULL;

  return dll->tail;
}

struct node_t* dll_begin(struct doubly_linked_list_t* dll){
  if(!dll || !dll->head) return NULL;

  return dll->head;
}

int dll_size(const struct doubly_linked_list_t* dll){
  if(!dll) return -1;
  if(!dll->head) return 0;

  struct node_t *pHead = dll->head;
  int count = 0;
  while(pHead){
    struct node_t *temp;
    temp = pHead->next;
    count++;
    pHead = temp;
  }

  return count;
}

int dll_is_empty(const struct doubly_linked_list_t* dll){
  if(!dll) return -1;
  else if(!dll->head) return 1;
  return 0;
}

int dll_at(const struct doubly_linked_list_t* dll, unsigned int index, int *err_code){
  if(!dll || !dll->head || !dll->tail){
    if(err_code) *err_code = 1;
    return -1;
  }
  int size = dll_size(dll);
  if((int)index>=size){
    if(err_code) *err_code = 1;
    return -1;
  }

  if((int)index==0){
    if(err_code) *err_code = 0;
    return dll->head->data;
  }
  if((int)index==size-1){
    if(err_code) *err_code = 0;
    return dll->tail->data;
  }

  struct node_t *temp = dll->head;
  for(int i=0; i<(int)index; i++)
    temp = temp->next;
  
  if(err_code) *err_code = 0;

  return temp->data;
}

int dll_insert(struct doubly_linked_list_t* dll, unsigned int index, int value){
  if(!dll || (int)index<0) return 1;
  int size = dll_size(dll), spr;
  if((int)index>size) return 1;

  if((int)index==0){
    spr = dll_push_front(dll, value);
    if(spr!=0) return 2;
    return 0;
  }
  if((int)index==size){
    spr = dll_push_back(dll, value);
    if(spr!=0) return 2;
    return 0;
  }

  struct node_t *pNode = (struct node_t*)malloc(sizeof(struct node_t));
  if(!pNode) return 2;

  pNode->data = value;

  struct node_t *temp = dll->head;
  for(int i=1; i<(int)index; i++)
    temp = temp->next;

  pNode->next = temp->next;
  temp->next = pNode;
  pNode->next->prev = pNode;
  pNode->prev = temp;

  return 0;
}

int dll_remove(struct doubly_linked_list_t* dll, unsigned int index, int *err_code){
  if(!dll || (int)index<0 || !dll->head){
    if(err_code) *err_code = 1;
    return -1;
  }
  int res = 0;
  int size = dll_size(dll), spr;
  if((int)index>=size){
    if(err_code) *err_code = 1;
    return -1;
  }

  if((int)index==0){
    spr = dll_pop_front(dll, err_code);
    return spr;
  }
  if((int)index==size-1){
    spr = dll_pop_back(dll, err_code);
    return spr;
  }
  struct node_t *temp, *pHead = dll->head;
  for(int i=1; i<(int)index; i++)
    pHead = pHead->next;
  
  temp = pHead->next;
  res = temp->data;
  pHead->next = pHead->next->next;
  temp->next->prev = pHead;

  free(temp);
  if(err_code) *err_code = 0;
  return res;
}

void dll_clear(struct doubly_linked_list_t* dll){
  if(!dll || !dll->head || !dll->tail) return;

  struct node_t *pHead = dll->head;
  while(pHead){
    struct node_t *temp;
    temp = pHead->next;
    free(pHead);
    pHead = temp;
  }
  dll->head = NULL;
  dll->tail = NULL;
}

void dll_display(const struct doubly_linked_list_t* dll){
  if(!dll || !dll->head || !dll->tail) return;

  struct node_t *temp;
  temp = dll->head;
  while(temp){
    printf("%d ", temp->data);
    temp = temp->next;
  }
  printf("\n");
}

void dll_display_reverse(const struct doubly_linked_list_t* dll){
  if(!dll || !dll->head || !dll->tail) return;

  struct node_t *temp;
  temp = dll->tail;
  while(temp){
    printf("%d ",temp->data);
    temp = temp->prev;
  }
  printf("\n");
}

