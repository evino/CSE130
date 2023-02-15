#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#include "queue.h"

struct queue{
    int count;
    int size;

    int in;
    int out;

    // int push_rc;
    // int pop_rc;

    pthread_mutex_t mutex_push;
    pthread_mutex_t mutex_pop;

    // int cv_rc;
    pthread_cond_t push_cv; // Might need seperate ones for push() & pop()
    pthread_cond_t pop_cv;

    void **arr;
};// Need queue here?




queue_t *queue_new(int size) {
    queue_t *q = malloc(sizeof(queue_t));
    q->count = 0;
    q->size = size;

    q->in = 0;
    q->out = 0;

    q->arr = malloc(size * sizeof(void *));

    // q->push_rc = pthread_mutex_init(&(q->mutex_push), NULL);
    // assert(!(q->push_rc));
    assert(!(pthread_mutex_init(&(q->mutex_push), NULL)));

    // q->pop_rc = pthread_mutex_init(&(q->mutex_pop), NULL);
    // assert(!(q->pop_rc));
    assert(!(pthread_mutex_init(&(q->mutex_pop), NULL)));

    // q->cv_rc = pthread_cond_init(&(q->cv), NULL);
    // assert(!(q->cv_rc));

    assert(!(pthread_cond_init(&(q->push_cv), NULL)));
    assert(!(pthread_cond_init(&(q->pop_cv), NULL)));

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
        pthread_cond_wait(&(q->push_cv), &(q->mutex_push));
    }

    pthread_mutex_lock(&q->mutex_push);

    q->arr[q->in] = elem;
    q->in = (q->in + 1) % q->size;
    q->count += 1;

    pthread_mutex_unlock(&q->mutex_push);

    pthread_cond_signal(&q->pop_cv);
    return true;
}

bool queue_pop(queue_t *q, void **elem) {
    if (q == NULL) {
        return false;
    }

    while (q->count == 0) {
        pthread_cond_wait(&q->pop_cv, &q->mutex_pop);
    }

    pthread_mutex_lock(&q->mutex_pop);

    *elem = q->arr[q->out];
    q->out = (q->out + 1) % q->size;
    q->count -= 1;

    pthread_mutex_unlock(&q->mutex_pop);

    pthread_cond_signal(&q->pop_cv);

    return true;
}

int getCount(queue_t *q) {  // FOR DEBUG. REMOVE WHEN DONE
    return q->count;
}
