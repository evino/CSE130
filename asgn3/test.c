#include <stdio.h>
#include <pthread.h>

#include "queue.h"

int main() {
    pthread_t t1;


    queue_t *myQueue = queue_new(15);

    uintptr_t x = 4;
    // typedef struct {
    //     queue_t *q;
    //     void *elem;
    // } args;
    // args queueArgs;
    // queueArgs.q = myQueue;

    // pthread_create(&t1, NULL, queue_push, [myQueue, (void*)x]);
    queue_push(myQueue, (void *)&x);
    uintptr_t r;
    queue_pop(myQueue, (void **)&r);
    // queue_pop(myQueue, (void **)&r);

    // queue_push(myQueue, (void*)&x);

    queue_delete(&myQueue);


    return 0;

}
