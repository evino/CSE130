#include <stdlib.h>
#include <unistd.h>

#include "helpers.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        return (invalid_port());
    }

    int port = atoi(argv[1]);
    if (port < 1 || port > 65535) {
        return (invalid_port());
    }
    return 0;
}
