#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

#define MAX_LEN 1024
//#define BUFF_LEN 1024

int main() {
    // char commandBuffer[MAX_LEN];
    // char command[MAX_LEN];
    // char file[MAX_LEN];
    char buffer[MAX_LEN] = "";
    char command[MAX_LEN] = "";
    char file[MAX_LEN] = "";
    
    ssize_t bytes = read(0, buffer, sizeof(buffer));
    sscanf(buffer, "%s %s", command, file);

    int fd = open(file, O_RDWR);
    if ((fd == -1) || (strlen(file) >= PATH_MAX)) {
        write(2, "Invalid Command\n", strlen("Invalid Command\n"));
        //close(fd);
        return 1;
    }

    if (strcmp(command, "get") == 0) {

        // SWITCH TO USE ONE BUFFER
        while (bytes > 0) {
            bytes = read(fd, buffer, sizeof(buffer));
            write(1, buffer, bytes);
        //     //write(1, "\n", strlen(buffer));
        }

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
