#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "queue.h"

#define queue_size 5

struct Push_Args {
    queue_t *q;
    void *elem;
};

// void *push(void *args) {
//     // struct Push_Args *pushInfo = args;
//     //queue_push(pushInfo->q, pushInfo->elem);
//     // (Push_Args *)args;
//     // queue_push(((Push_Args *)args)->q, (void *)((Push_Args *)args)->elem);
//     return NULL;
// }

int main() {
    queue_t *myQueue = queue_new(queue_size);
    if (myQueue == NULL) {
        return 1;
    }

    pthread_t t1;

    uintptr_t x = 1;
    // struct Push_Args *t1_arg = {myQueue, &x};
    struct Push_Args *t1_arg;
    t1_arg = malloc(sizeof(t1_arg));
    t1_arg->q = myQueue;

    // t1_arg->q = queue;
    // uintptr_t x = 15;
    // t1_arg->elem = &x;

    // pthread_create(&t1, NULL, push, (void *)&t1_arg);


}
