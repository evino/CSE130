#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "queue.h"

#define queue_size 5

struct Push_Args {
    queue_t *q;
    void *elem;
};

struct Pop_Args {
    queue_t *q;
    void **elem;
};

void *push(void *args) {
    struct Push_Args *pushArgs = (struct Push_Args *)args;

    // queue_t *q = pushArgs->q;

    fprintf(stderr, "%lu\n", (uintptr_t)pushArgs->elem);
            fprintf(stderr, "db\n");
    // uintptr_t intgr = (uintptr_t)pushArgs->elem;

    queue_push(pushArgs->q, pushArgs->elem);


    // struct Push_Args *pushInfo = args;
    //queue_push(pushInfo->q, pushInfo->elem);
    // (Push_Args *)args;
    // queue_push(((Push_Args *)args)->q, (void *)((Push_Args *)args)->elem);
    fprintf(stderr, "db2\n");
    return NULL;
}


void *pop(void *args) {
    struct Pop_Args *popArgs = (struct Pop_Args *)args;

    queue_pop(popArgs->q, (void *)(popArgs->elem));

    return NULL;
}

int main() {
    queue_t *myQueue = queue_new(queue_size);
    if (myQueue == NULL) {
        return 1;
    }


    uintptr_t one = 1;
    // struct Push_Args *t1_arg = {myQueue, &x};
    struct Push_Args *t1_arg = malloc(sizeof(t1_arg));
    t1_arg->q = myQueue;
    t1_arg->elem = (void *)one;
    // push((void *)t1_arg);

    // printf("%lu\n", (uintptr_t)t1_arg->elem);
    pthread_t t1;
    pthread_create(&t1, NULL, push, (void *)&t1_arg);

    void *rc;
    pthread_join(t1, &rc);

    // uintptr_t two = 2;
    // struct Push_Args *t2_arg = malloc(sizeof(t2_arg));
    // t2_arg->q = myQueue;
    // t2_arg->elem = (void *)two;
    // push

    // t1_arg->q = queue;
    // uintptr_t x = 15;
    // t1_arg->elem = &x;

    // pthread_create(&t1, NULL, push, (void *)&t1_arg);


}
