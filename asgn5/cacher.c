#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "fifo.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Missing arguments\n");
        return 1;
    }
    uintptr_t cache_size = atol(argv[1]);
    printf("Cache size: %lu\n", cache_size);  // DB
    int cache_policy = 0; // 0 is default for fifo
    //void *elem = malloc(8 * sizeof(void *));

    if (cache_policy == 0) {

        fifo_t *cache = fifo_new(cache_size);

        void *elem = NULL;
        char c = '\0';

        int bytes_read = 0;
        do {
            bytes_read = fscanf(stdin, "%c", &c);
            elem = (void *) &c;
            fifo_push(cache, elem);

        } while (bytes_read != EOF);
        
        // do {
            
        //     bytes_read = fread((void *) elem, sizeof(void *), 8, 0);
        //     printf("DB\n");
        // } while (bytes_read > 0);
    }


    return 0;
}
