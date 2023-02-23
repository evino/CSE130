#include <stdio.h>
#include <pthread.h>

#include "queue.h"

#define queue_size 5

typedef struct {
    queue_t *q;
    void *elem;
} Push_Args;

void *push(void *args) {
    Push_Args *pushInfo = args;
    queue_push(pushInfo->q, pushInfo->elem);
    return NULL;
}

int main() {
    queue_t *queue = queue_new(queue_size);
    if (queue == NULL) {
        return 1;
    }

    pthread_t t1;

    Push_Args *t1_arg;
    t1_arg->q = queue;
    uintptr_t x = 15;
    t1_arg->elem = &x;

    pthread_create(&t1, NULL, push, (void *)&t1_arg);


}
