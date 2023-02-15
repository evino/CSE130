#include <stdlib.h>
#include <pthread.h>
#include "queue.h"


typedef struct {
    int length;

    int front;
    int rear;

    pthread_mutex_t mutex_push;
    pthread_mutex_t mutex_pop;

    void **arr;
} queue; // Need queue here?


queue_t *queue_new(int size) {
    //queue_t q = malloc(sizeof(queue_t));

}
