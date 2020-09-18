#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "doubly_linked_list.h"
#include "tested_declarations.h"
#include "rdebug.h"

struct doubly_linked_list_t* dll_create()
{
  struct doubly_linked_list_t *dll = (struct doubly_linked_list_t*)malloc(sizeof(struct doubly_linked_list_t));
  if (!dll) return NULL;

  dll->head = NULL;
  dll->tail = NULL;

  return dll;
}

int dll_push_back(struct doubly_linked_list_t* dll, int value)
{
  if (!dll) return 1;

  struct node_t *new_node = (struct node_t*)malloc(sizeof(struct node_t));
  if (!new_node) return 2;

  if (!dll->tail)
  {
    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    dll->head = new_node;
    dll->tail = new_node;
  }
  else
  {
    new_node->data = value;
    dll->tail->next = new_node;
    new_node->prev = dll->tail;
    dll->tail = new_node;
    dll->tail->next = NULL;
  }

  return 0;
}

int dll_push_front(struct doubly_linked_list_t* dll, int value)
{
  if (!dll) return 1;

  struct node_t *new_node = (struct node_t*)malloc(sizeof(struct node_t));
  if (!new_node) return 2;

  if (!dll->head)
  {
    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    dll->head = new_node;
    dll->tail = new_node;
  }
  else
  {
    new_node->data = value;
    new_node->next = dll->head;
    dll->head->prev = new_node;
    dll->head = new_node;
    dll->head->prev = NULL;
  }

  return 0;
}

int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code)
{
  if (!dll || !dll->head || !dll->tail)
  {
    if (err_code) *err_code = 1;
    return -1;
  }

  int res = dll->tail->data;
  struct node_t *tmp = dll->head;
  if (tmp->next)
  {
    free(dll->tail);
    while (tmp->next!=dll->tail) tmp = tmp->next;
    dll->tail = tmp;
    dll->tail->next = NULL;
  }
  else
  {
    tmp = dll->tail;
    free(tmp);
    dll->head = NULL;
    dll->tail = NULL;
  }

  if (err_code) *err_code = 0;

  return res;
}

int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code)
{
  if (!dll || !dll->head || !dll->tail)
  {
    if (err_code) *err_code = 1;
    return -1;
  }

  int res = dll->head->data;
  struct node_t *tmp = dll->head;
  if (tmp->next)
  {
    free(tmp);
    dll->head = dll->head->next;
    dll->head->prev = NULL;
  }
  else
  {
    dll->tail = NULL;
    free(tmp);
    dll->head = NULL;
  }

  if (err_code) *err_code = 0;

  return res;
}

int dll_back(const struct doubly_linked_list_t* dll, int *err_code)
{
  if (!dll || !dll->tail)
  {
    if (err_code) *err_code = 1;
    return -1;
  }

  if (err_code) *err_code = 0;

  return dll->tail->data;
}

int dll_front(const struct doubly_linked_list_t* dll, int *err_code)
{
  if (!dll || !dll->head)
  {
    if (err_code) *err_code = 1;
    return -1;
  }

  if (err_code) *err_code = 0;

  return dll->head->data;
}

struct node_t* dll_end(struct doubly_linked_list_t* dll)
{
  if (!dll || !dll->head) return NULL;

  return dll->tail;
}

struct node_t* dll_begin(struct doubly_linked_list_t* dll)
{
  if (!dll || !dll->head) return NULL;

  return dll->head;
}

int dll_size(const struct doubly_linked_list_t* dll)
{
  if (!dll) return -1;
  if (!dll->head) return 0;

  struct node_t *headp = dll->head;
  int count = 0;
  while (headp)
  {
    struct node_t *tmp;
    tmp = headp->next;
    count++;
    headp = tmp;
  }

  return count;
}

int dll_is_empty(const struct doubly_linked_list_t* dll)
{
  if (!dll) return -1;
  else if (!dll->head) return 1;
  return 0;
}

int dll_at(const struct doubly_linked_list_t* dll, unsigned int index, int *err_code)
{
  if (!dll || !dll->head || !dll->tail)
  {
    if (err_code) *err_code = 1;
    return -1;
  }
  int size = dll_size(dll);
  if ((int)index>=size)
  {
    if (err_code) *err_code = 1;
    return -1;
  }

  if ((int)index==0)
  {
    if (err_code) *err_code = 0;
    return dll->head->data;
  }
  if ((int)index==size-1)
  {
    if (err_code) *err_code = 0;
    return dll->tail->data;
  }

  struct node_t *tmp = dll->head;
  for (int i=0; i<(int)index; i++)
  {
    tmp = tmp->next;
  }

  if (err_code) *err_code = 0;

  return tmp->data;
}

int dll_insert(struct doubly_linked_list_t* dll, unsigned int index, int value)
{
  if (!dll || (int)index<0) return 1;
  int size = dll_size(dll), spr;
  if ((int)index>size) return 1;

  if ((int)index==0)
  {
    spr = dll_push_front(dll, value);
    if (spr!=0) return 2;
    return 0;
  }
  if ((int)index==size)
  {
    spr = dll_push_back(dll, value);
    if (spr!=0) return 2;
    return 0;
  }

  struct node_t *new_node = (struct node_t*)malloc(sizeof(struct node_t));
  if (!new_node) return 2;

  new_node->data = value;

  struct node_t *tmp = dll->head;
  for (int i=1; i<(int)index; i++)
  {
    tmp = tmp->next;
  }

  new_node->next = tmp->next;
  tmp->next = new_node;

  new_node->next->prev = new_node;
  new_node->prev = tmp;

  return 0;
}

int dll_remove(struct doubly_linked_list_t* dll, unsigned int index, int *err_code)
{
  if (!dll || (int)index<0 || !dll->head)
  {
    if (err_code) *err_code = 1;
    return -1;
  }
  int size = dll_size(dll), spr;
  if ((int)index>=size)
  {
    if (err_code) *err_code = 1;
    return -1;
  }

  if ((int)index==0)
  {
    spr = dll_pop_front(dll, err_code);
    return spr;
  }
  if ((int)index==size-1)
  {
    spr = dll_pop_back(dll, err_code);
    return spr;
  }

  int res;
  struct node_t *tmp, *p_head = dll->head;
  for (int i=1; i<(int)index; i++)
  {
    p_head = p_head->next;
  }

  tmp = p_head->next;
  res = tmp->data;
  p_head->next = p_head->next->next;

  tmp->next->prev = p_head;

  free(tmp);

  if (err_code) *err_code = 0;

  return res;
}

void dll_clear(struct doubly_linked_list_t* dll)
{
  if (!dll || !dll->head || !dll->tail) return;

  struct node_t *headp = dll->head;
  while (headp)
  {
    struct node_t *tmp;
    tmp = headp->next;
    free(headp);
    headp = tmp;
  }
  dll->head = NULL;
  dll->tail = NULL;
}

void dll_display(const struct doubly_linked_list_t* dll)
{
  if (!dll || !dll->head || !dll->tail) return;

  struct node_t *tmp;
    tmp = dll->head;
    while (tmp)
    {
      printf("%d ", tmp->data);
      tmp = tmp->next;
    }
    printf("\n");
}

void dll_display_reverse(const struct doubly_linked_list_t* dll)
{
  if (!dll || !dll->head || !dll->tail) return;

  struct node_t *tmp;
    tmp = dll->tail;
    while (tmp)
    {
      printf("%d ", tmp->data);
      tmp = tmp->prev;
    }
    printf("\n");
}

