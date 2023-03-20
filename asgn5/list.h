#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct list list_t;

// Create a new list
list_t *list_new();

// Push an element to a list
void list_push(list_t *, void *);

// Delete/free list
void list_delete(list_t *);

// Return true if list contains specific
// element. Otherwise return false.
bool list_contains(list_t *, void *);

// Move cursor to front node of list.
void list_front(list_t *);

// Move current node in list to next node.
void list_next(list_t *);

// Delete head node of list.
void delete_head(list_t *);

#endif
