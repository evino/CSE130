#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

// Make private
// typedef struct node node_t;

//node_t *node_new(void *elem);


typedef struct list list_t;

// Create a new list to hold history of
// elements in a cache.
list_t *list_new();

void list_push(list_t *l, void *elem);

void list_delete(list_t *l);

bool list_search(list_t *l, void *elem);

#endif
