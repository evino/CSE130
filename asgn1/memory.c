#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

#define MAX_LEN 8192

int main() {
    char buffer[MAX_LEN] = "";
    char command[MAX_LEN] = "";
    char file[MAX_LEN] = "";

    ssize_t bytes = read(0, buffer, MAX_LEN);
    sscanf(buffer, "%s %s", command, file);

    int fd = open(file, O_RDWR);

    if (strlen(file) > PATH_MAX) { // File name len exceed
        write(2, "Invalid Command\n", strlen("Invalid Command\n"));
        return 1;
    }

    if (strcmp(command, "get") == 0) {
        if (fd == -1) { // Invalid File
            write(2, "Invalid Command\n", strlen("Invalid Command\n"));
            return 1;
        }

        // SWITCH TO USE ONE BUFFER
        while (bytes > 0) {
            bytes = read(fd, buffer, 4096);
            write(1, buffer, bytes);
        }

        if (bytes == -1) { // If write fails
            write(2, "Operation Failed\n", strlen("Operation Failed\n"));
            return 1;
        }

        close(fd);
    } else if (strcmp(command, "set") == 0) {
        printf("set\n");
    } else {
        write(2, "Invalid Command\n", strlen("Invalid Command\n"));
        return 1;
    }
    return 0;
}
