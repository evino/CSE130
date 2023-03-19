#include <stdlib.h>

#include "list.h"

typedef struct node node_t;

struct node {
    void *data;
    node_t *next;
    node_t *prev;
};

node_t *node_new(void *elem) {
    node_t *n = malloc(sizeof(node_t));
    n->data = elem;
    n->next = NULL;
    n->prev = NULL;

    return n;
}

void node_delete(node_t *n) {
    free(n);
    n = NULL;
    return;
}
