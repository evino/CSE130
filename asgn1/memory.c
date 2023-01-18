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
    ssize_t writeVal;
    if (bytes == -1) {
        write(2, "Operation Failed\n", strlen("Operation Failed\n"));
        return 1;
    }
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
        while (bytes > 0 && writeVal > -1) {
            bytes = read(fd, buffer, 4096);
            writeVal = write(1, buffer, bytes);
        }

        close(fd); // This was moved up

        if (bytes == -1 || writeVal == -1) { // If write fails
            write(2, "Operation Failed\n", strlen("Operation Failed\n"));
            return 1;
        }

    } else if (strcmp(command, "set") == 0) {
        //if (fd == -1) {
        //fd = open(file, S_IRWXU | O_RDWR | O_TRUNC | O_CREAT);
        fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
        // while (bytes > 0 && writeVal > -1) {
        while (bytes >= 0) {
            bytes = read(0, buffer, 4096);
            writeVal = write(fd, buffer, bytes);
        }

        return 0;
        //}
    } else {
        write(2, "Invalid Command\n", strlen("Invalid Command\n"));
        return 1;
    }
    return 0;
}
