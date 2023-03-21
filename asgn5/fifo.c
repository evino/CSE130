#include <stdlib.h>
#include <stdio.h>

#include "fifo.h"
#include "list.h"
#include "queue.h"

struct fifo {
    int count;
    queue_t *fifo_cache;
    list_t *fifo_hist;
    int compulsory_miss;
    int capacity_miss;
};

fifo_t *fifo_new(int size) {
    fifo_t *cache = malloc(sizeof(fifo_t));
    cache->count = 0;
    cache->fifo_cache = queue_new(size);
    cache->fifo_hist = list_new();
    cache->compulsory_miss = 0;
    cache->capacity_miss = 0;

    return cache;
}

void fifo_push(fifo_t *f, void *elem) {
    //if (f->count == (f->fifo_cache)->size) {  // Eviction needs to happen
    // if (f->count == queue_size(f->fifo_cache)) {
    //     fprintf(stdout, "MISS\n");
    // }
    // f->count++;
    queue_push(f->fifo_cache, elem);
    list_push(f->fifo_hist, elem);
}

int fifo_size(fifo_t *f) {
    return (queue_count(f->fifo_cache));
}

bool fifo_search(fifo_t *f, void *target) {
    return (queue_search(f->fifo_cache, target));
}
