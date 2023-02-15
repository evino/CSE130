#include <stdio.h>

#include "queue.h"

int main() {
    queue_t *myQueue = queue_new(15);

    int x = 4;
    queue_push(myQueue, &x);
    printf("%d\n", getCount(myQueue));

    return 0;

}
