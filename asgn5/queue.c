#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <semaphore.h>
#include <stdint.h>

#include <stdio.h>

#include "queue.h"

struct queue {
    int count;
    int size;

    int in;
    int out;

    void **arr;
};

queue_t *queue_new(int size) {

    if (size <= 0) {
        return false;
    }

    queue_t *q = malloc(sizeof(queue_t));
    q->count = 0;

    q->size = size;

    q->in = 0;
    q->out = 0;

    q->arr = malloc(size * sizeof(void *));

    return q;
}

void queue_delete(queue_t **q) {
    assert(q != NULL || *q != NULL);

    free((*q)->arr);
    free(*q);
    *q = NULL;

    return;
}

bool queue_push(queue_t *q, void *elem) {
    if (q == NULL) {
        return false;
    }

    if (q->count == q->size) {
        return false;
    }

    q->arr[q->in] = elem;

    // for (int i = q->out; i < q->in - 1; i++) {
    //     printf("push db: %s\n", (char *) q->arr[i]);
    // }

    q->in = (q->in + 1) % q->size;

    // Ensuring count is atomic, i.e. calling PUSH() and
    // POP() doesn't result in weird behavoir in the count.
    q->count += 1;

    return true;
}

bool queue_pop(queue_t *q, void **elem) {
    if (q == NULL) {
        return false;
    }

    if (q->count == 0) {
        return false;
    }

    *elem = q->arr[q->out];
    q->out = (q->out + 1) % q->size;

    // Ensuring count is atomic, i.e. calling PUSH() and
    // POP() doesn't result in weird behavoir in the count.
    q->count -= 1;

    return true;
}

int queue_size(queue_t *q) {
    return q->size;
}

int queue_count(queue_t *q) {
    return q->count;
}

bool queue_search(queue_t *q, void *target) {
    // printf("out: %d\nin: %d\n", q->out, q->in);
    // fprintf(stderr,"at out, its %lu\n", (uintptr_t) q->arr[q->out]);
    for (int i = q->out; i < q->in; i++) {
        if ((uintptr_t) q->arr[i] == (uintptr_t) target) {
            fprintf(stderr, "%lu exists @ index %d\n", (uintptr_t) q->arr[i], i);
            return true;
        }
        fprintf(stderr, "%lu @ index %d\n", (uintptr_t) q->arr[i], i);
    }

    if ((uintptr_t) target == 1) { // TO SILENCE WARNING
        return true;
    }

    return false;
}
