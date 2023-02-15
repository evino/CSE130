#include <stdlib.h>
#include <pthread.h>
#include "queue.h"

typedef struct {
    int length;

    int front;
    int rear;

    int push_rc;
    int pop_rc;

    pthread_mutex_t mutex_push;
    pthread_mutex_t mutex_pop;

    void **arr;
} queue; // Need queue here?

queue_t *queue_new(int size) {
    queue *q = malloc(sizeof(queue));
    q->length = 0;
    q->front = 0;
    q->rear = 0;

    q->arr = malloc(size * sizeof(void *));

    q->push_rc = pthread_mutex_init(&(q->mutex_push), NULL);
    q->pop_rc = pthread_mutex_init(&(q->mutex_pop), NULL);

    return q;
}
