#include <stdlib.h>

#include "fifo.h"
#include "list.h"
#include "queue.h"

struct fifo {
    int count;
    queue_t *fifo_cache;
    list_t *fifo_hist;
};

fifo_t *fifo_new(int size) {
    fifo_t *cache = malloc(sizeof(fifo_t));
    cache->count = 0;
    cache->fifo_cache = queue_new(size);
    cache->fifo_hist = list_new();

    return cache;
}

void fifo_push(fifo_t *cache, void *elem) {
    cache->count++;
    queue_push(cache->fifo_cache, elem);
    list_push(cache->fifo_hist, elem);
}
