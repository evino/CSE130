#include <string.h>
#include <unistd.h>

#include "helpers.h"

int invalid_port() {
    write(2, "Invalid Port\n", strlen("Invalid Port\n"));
    return 1;
}
