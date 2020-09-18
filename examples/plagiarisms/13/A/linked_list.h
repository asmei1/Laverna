#include <stdio.h>
#include <stdarg.h>
#ifndef __linked_list__h
#define __linked_list__h

struct linked_list_t
{
  struct node_t *head;
  struct node_t *tail;
};

struct node_t
{
  char *data;
  struct node_t *next;
};

struct linked_list_t* ll_create();

int ll_push_back(struct linked_list_t* ll, char *value);
int ll_push_front(struct linked_list_t* ll, char *value);

int ll_size(const struct linked_list_t* ll);
int ll_is_empty(const struct linked_list_t* ll);

int ll_insert(struct linked_list_t* ll, unsigned int index, char *value);

void ll_clear(struct linked_list_t* ll);

void ll_display(const struct linked_list_t* ll);

int ll_is_sorted_ascending(const struct linked_list_t* ll);
int ll_insert_words(struct linked_list_t* ll, int N, ...);

#endif

