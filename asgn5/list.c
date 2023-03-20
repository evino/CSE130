#include <stdlib.h>
#include <stdio.h>

#include "list.h"

typedef struct node node_t;

// Node ADT
struct node {
    void *data;
    node_t *next;
    // node_t *prev;
};

node_t *node_new(void *elem) {
    node_t *n = malloc(sizeof(node_t));
    n->data = elem;
    n->next = NULL;
    // n->prev = NULL;

    return n;
}

void node_delete(node_t *n) {
    // n->data = NULL;
    // n->next = NULL;
    free(n);
    n = NULL;
    return;
}

// List ADT
struct list {
    size_t size;
    node_t *head;
    node_t *tail;
    node_t *cur;
};

list_t *list_new() {
    list_t *l = malloc(sizeof(list_t));
    l->size = 0;
    l->head = NULL;
    l->tail = NULL;
    l->cur = NULL;
    return l;
}

void delete_head(list_t *l) {
    // list_front(l);
    if (l->size == 0) {
        fprintf(stderr, "ERROR: CALLING delete_head on list of size 0.\n");
    }
    node_t *next_temp = node_new((void *) l->head->next);
    l->head = next_temp;
    return;
}

// void list_delete(list_t *l) {
//     list_front(l);

// }

void list_push(list_t *l, void *elem) {
    node_t *n = node_new(elem);
    if (l->size == 0) {
        l->head = n;
        l->tail = n;
    } else {
        l->tail->next = n;
        l->tail = n;
    }
    l->cur = l->tail;
    l->size++;
    return;
}

void list_front(list_t *l) {
    l->cur = l->head;
    return;
}

void list_next(list_t *l) {
    l->cur = l->cur->next;
    return;
}

bool list_contains(list_t *l, void *elem) {
    list_front(l);
    while (l->cur != NULL) {
        if (l->cur->data == elem) {
            return true;
        }
        list_next(l);
    }
    return false;
}
