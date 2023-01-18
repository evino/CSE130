#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

#define MAX_LEN 8192
//#define BUFF_LEN 1024

int main() {
    // char commandBuffer[MAX_LEN];
    // char command[MAX_LEN];
    // char file[MAX_LEN];
    char buffer[MAX_LEN] = "";
    char command[MAX_LEN] = "";
    char file[MAX_LEN] = "";
    
    ssize_t bytes = read(0, buffer, MAX_LEN);
    ssize_t byteCount = bytes;
    sscanf(buffer, "%s %s", command, file);
    if (strlen(file) > PATH_MAX) {  // File name len exceed
        write(2, "Invalid Command\n", strlen("Invalid Command\n"));
        return 1;
    }
    if (byteCount > MAX_LEN) {
        write(2, "Operation Failed\n", strlen("Operation Failed\n"));
        return 1;
    }

    //printf("%zu\n", bytes);

    if (strcmp(command, "get") == 0) {
        int fd = open(file, O_RDWR);
        if (fd == -1) {  // Invalid File
            write(2, "Invalid Command\n", strlen("Invalid Command\n"));
            return 1;
        }


        // SWITCH TO USE ONE BUFFER
        while (bytes > 0) {
            bytes = read(fd, buffer, 4096);
            byteCount += bytes;
            //printf("%zu\n", bytes);
            if (byteCount > MAX_LEN) {
                write(2, "Operation Failed\n", strlen("Operation Failed\n"));
                return 1;
            }
            write(1, buffer, bytes);
            //printf("\n\nBuff: %s\n", buffer);

        //     //write(1, "\n", strlen(buffer));
        }

        //printf("%zu\n", byteCount);
        //printf("%s\n", file);

        close(fd);

    } else if (strcmp(command, "set") == 0) {
        printf("set\n");
    } else {
        write(2, "Invalid Command\n", strlen("Invalid Command\n"));
        return 1;
    }
    return 0;
}
