#pragma once
#include <stdbool.h>

typedef struct fifo fifo_t;

// Builds up a new fifo cache
fifo_t *fifo_new(int size);
// Need arr to hold cache elems
// Need history list

// Clears Cache, and frees all
// memory associated with it
void fifo_delete(fifo_t **f);

void fifo_push(fifo_t *f, void *elem);

// Print out miss type, and update miss count
void fifo_miss(fifo_t *f);
