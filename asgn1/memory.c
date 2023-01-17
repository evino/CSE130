#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LEN 64

int main() {
    char commandBuffer[MAX_LEN] = "";
    char command[MAX_LEN] = "";
    char file[MAX_LEN] = "";
    read(0, commandBuffer, 32);
    sscanf(commandBuffer, "%s %s", command, file);
    int fd = open(file, O_RDWR);

    if (strcmp(command, "get") == 0) {
        if (fd == -1) {
            write(2, "Invalid Command\n", strlen("Invalid Command\n"));
            return 1;
        }



        //printf("%s\n", file);

    } else if (strcmp(command, "set") == 0) {
        printf("set\n");
    } else {
        printf("ERR\n");
        return 1;
    }
    return 0;
}
