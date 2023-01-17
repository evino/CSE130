#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_LEN 64

int main() {
    char commandBuffer[MAX_LEN] = "";
    char command[MAX_LEN] = "";
    char file[MAX_LEN] = "";
    read(0, commandBuffer, 32);
    sscanf(commandBuffer, "%s %s", command, file);
    if (strcmp(command, "get") == 0) {
        printf("%s\n", file);
    } else if (strcmp(command, "set") == 0) {
        printf("set\n");
    } else {
        printf("ERR\n");
        return 1;
    }
    return 0;
}
