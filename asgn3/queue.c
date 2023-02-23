#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

#include "queue.h"

struct queue {
    // int count;
    sem_t countSem;

    int size;

    int in;
    int out;

    pthread_mutex_t mutex_push;
    pthread_mutex_t mutex_pop;

    pthread_cond_t push_cv; // Might need seperate ones for push() & pop()
    pthread_cond_t pop_cv;

    void **arr;
};

queue_t *queue_new(int size) {
    queue_t *q = malloc(sizeof(queue_t));
    // q->count = 0;
    assert(!(sem_init(&q->countSem, 0, 0)));



    q->size = size;

    q->in = 0;
    q->out = 0;

    q->arr = malloc(size * sizeof(void *));

    assert(!(pthread_mutex_init(&(q->mutex_push), NULL)));
    assert(!(pthread_mutex_init(&(q->mutex_pop), NULL)));

    assert(!(pthread_cond_init(&(q->push_cv), NULL)));
    assert(!(pthread_cond_init(&(q->pop_cv), NULL)));

    return q;
}

void queue_delete(queue_t **q) {
    assert(q != NULL || *q != NULL);

    pthread_mutex_destroy(&((*q)->mutex_push));
    pthread_mutex_destroy(&((*q)->mutex_pop));

    pthread_cond_destroy(&((*q)->push_cv));
    pthread_cond_destroy(&((*q)->pop_cv));

    sem_destroy(&(*q)->countSem);

    // DESTROY SEM!!!

    free((*q)->arr);
    free(*q);
    *q = NULL;

    return;
}

bool queue_push(queue_t *q, void *elem) {
    if (q == NULL) {
        return false;
    }


    pthread_mutex_lock(&q->mutex_push);

    int count = -999;
    // assert(!(sem_getvalue(&q->countSem, &count)));
    sem_getvalue(&q->countSem, &count);
    while (count == q->size) {
        pthread_cond_wait(&(q->push_cv), &(q->mutex_push));
    }

    q->arr[q->in] = elem;
    q->in = (q->in + 1) % q->size;
    // q->count += 1;
    sem_post(&q->countSem);

    pthread_mutex_unlock(&q->mutex_push);
    pthread_cond_signal(&q->pop_cv);

    return true;
}

bool queue_pop(queue_t *q, void **elem) {
    if (q == NULL) {
        return false;
    }



    pthread_mutex_lock(&q->mutex_pop);

    int count = -999;
    // assert(!(sem_getvalue(&q->countSem, &count)));
    sem_getvalue(&(q->countSem), &count);

    while (count == 0) {
        pthread_cond_wait(&q->pop_cv, &q->mutex_pop);
    }

    *elem = q->arr[q->out];
    q->out = (q->out + 1) % q->size;
    sem_wait(&q->countSem);
    // q->count -= 1;

    pthread_mutex_unlock(&q->mutex_pop);
    pthread_cond_signal(&q->push_cv);

    return true;
}
