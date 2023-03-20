#include <stdlib.h>

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

void fifo_push(fifo_t *cache, void *elem) {
    if (cache->count == cache->fifo_cache->size) {  // Eviction needs to happen
        fprintf(stdout, "MISS\n";)
    }
    cache->count++;
    queue_push(cache->fifo_cache, elem);
    list_push(cache->fifo_hist, elem);
}


bool fifo_search(fifo_t *f, void *target) {
    for (int i = 0; i < f->count; i++) {
        if // Need to serach queue here instead
        
    }
}