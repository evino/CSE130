#include <stdint.h>
#include "list.h"

int main() {
    list_t *myList = list_new();
    uintptr_t x = 15;
    uintptr_t y = 11;
    char *c = "c";
    // char *d = "d";
    // uintptr_t z = 99;
    list_push(myList, (void *) x);
    list_push(myList, (void *) y);
    list_push(myList, (void *) c);

    bool contain = list_contains(myList, (void *) c);
    if (contain == true) {
        return 0;
    }
    return 1;
}
