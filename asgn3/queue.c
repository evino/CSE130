#include <stdlib.h>
#include <pthread.h>
#include "queue.h"

struct queue{
    int count;
    int size;

    int front;
    int rear;

    int push_rc;
    int pop_rc;

    pthread_mutex_t mutex_push;
    pthread_mutex_t mutex_pop;

    int cv_rc;
    pthread_cond_t cv; // Might need seperate ones for push() & pop()

    void **arr;
};// Need queue here?




queue_t *queue_new(int size) {
    queue_t *q = malloc(sizeof(queue_t));
    q->count = 0;
    q->size = size;

    q->front = 0;
    q->rear = 0;

    q->arr = malloc(size * sizeof(void *));

    q->push_rc = pthread_mutex_init(&(q->mutex_push), NULL);
    assert(!(q->push_rc));

    q->pop_rc = pthread_mutex_init(&(q->mutex_pop), NULL);
    assert(!(q->pop_rc));

    q->cv_rc = pthread_cond_init(&(q->cv), NULL);
    assert(!(q->cv_rc));

    return q;
}

// delete() {
// POP() till empty
// Then call free() on queue itself



bool queue_push(queue_t *q, void *elem) {
    if (q == NULL) {
        return false;
    }

    while (q->count == q->size) {
        pthread_cond_wait(&(q->cv), &(q->mutex_push));
    }
    q->arr[q->front] = elem;
    q->front = (q->front + 1) % q->size;
    q->count += 1;

    return true;
}
