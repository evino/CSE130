#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "fifo.h"

#define BUF_SIZE 4096




int main(int argc, char **argv) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Invalid arguments\n");
        return 1;
    }
    uintptr_t cache_size = atol(argv[1]);
    printf("Cache size: %lu\n", cache_size);  // DB
    int cache_policy = 0; // 0 is default for fifo
    //void *elem = malloc(8 * sizeof(void *));

    if (cache_policy == 0) {

        fifo_t *cache = fifo_new(cache_size);

        // void *elem = NULL;
        // char c = '\0';

        // int bytes_read = 0;
        //do {
        //     bytes_read = read(0, buf, 8);
        //     // printf("%d\n", bytes_read);
        //     elem = buf;
        //     // printf("%s\n", buffer);
        //     fifo_push(cache, elem);
        //     fprintf(stderr, "pushed db\n");
        // } while(bytes_read > 0);
        uintptr_t x = 78;
        uintptr_t mid = 65;
        uintptr_t y = 99;
        fifo_push(cache, (void *)x);
        fifo_push(cache, (void *) mid);
        fifo_push(cache, (void *)y);

        printf("Size of cache is %d \n", fifo_size(cache));
        uintptr_t target = 99;
        bool in = fifo_search(cache, (void *)target);
        fprintf(stderr, "%d\n", in);
        // do {
        //     bytes_read = fscanf(stdin, "%c", &c);
        //     elem = (void *) &c;
        //     fifo_push(cache, elem);

        // } while (bytes_read != EOF);
        
        // do {
            
        //     bytes_read = fread((void *) elem, sizeof(void *), 8, 0);
        //     printf("DB\n");
        // } while (bytes_read > 0);
    }


    return 0;
}
