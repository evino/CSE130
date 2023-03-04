#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "queue.h"

typedef struct Push_Args {
    queue_t *q;
    void *elem;
} Push_Args;

struct Pop_Args {
    queue_t *q;
    void **elem;
};

void *push(void *args) {
    Push_Args *pushArgs = (Push_Args *) args;

    if (pushArgs->q == NULL) {
        fprintf(stderr, "NULL\n");
    }

    // fprintf(stderr, "db\n");
    // uintptr_t intgr = (uintptr_t)pushArgs->elem;

    fprintf(stderr, "pusher called (%lu)\n", (uintptr_t) pushArgs->elem);
    queue_push(pushArgs->q, (void *) pushArgs->elem);
    fprintf(stderr, "Pushed: %lu\n", (uintptr_t) pushArgs->elem);

    return NULL;
}

void *pop(void *args) {
    struct Pop_Args *popArgs = (struct Pop_Args *) args;

    fprintf(stderr, "db\n");
    queue_pop(popArgs->q, (void *) (popArgs->elem));

    fprintf(stderr, "Popped: %lu\n", (uintptr_t) (*(popArgs->elem)));

    return NULL;
}

int main() {
    queue_t *myQueue = queue_new(1);

    if (myQueue == NULL) {
        return 1;
    }

    uintptr_t one = 1;

    struct Pop_Args *t2_arg = malloc(sizeof(t2_arg));
    t2_arg->q = myQueue;
    void *res = NULL;
    t2_arg->elem = &res;

    struct Push_Args *t1_arg = malloc(sizeof(t1_arg));
    t1_arg->q = myQueue;
    t1_arg->elem = (void *) one;

    // push((void *)t1_arg);
    // printf("%lu\n", (uintptr_t)t1_arg->elem);

    pthread_t t2;
    pthread_create(&t2, NULL, pop, (void *) t2_arg);

    pthread_t t1;
    pthread_create(&t1, NULL, push, (void *) t1_arg);

    pthread_t t3;
    struct Push_Args *t3_arg = malloc(sizeof(t3_arg));
    t3_arg->q = myQueue;
    uintptr_t t = 3;
    t3_arg->elem = (void *) t;
    pthread_create(&t3, NULL, push, (void *) t3_arg);

    void *rc1;
    void *rc2;
    void *rc3;
    pthread_join(t2, &rc2);

    pthread_join(t1, &rc1);
    pthread_join(t3, &rc3);

    // uintptr_t two = 2;
    // struct Push_Args *t2_arg = malloc(sizeof(t2_arg));
    // t2_arg->q = myQueue;
    // t2_arg->elem = (void *)two;
    // push

    // t1_arg->q = queue;
    // uintptr_t x = 15;
    // t1_arg->elem = &x;

    // pthread_create(&t1, NULL, push, (void *)&t1_arg);

    fprintf(stderr, "EOF\n");

    queue_delete(&myQueue);
    return 0;
}
