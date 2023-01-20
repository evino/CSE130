#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

#define BUFFER_SIZE 4096

int main() {
    char buffer[BUFFER_SIZE]; // Might need to initialize to silence valgrind error

    char *invalid = "Invalid Command\n";


    // read command and file from STDIN
    int bytes_read = read(0, buffer, BUFFER_SIZE);

    if (bytes_read == -1) {
        write(2, "Operation Failed\n", strlen("Operation Failed\n"));
        return 1;
    }

    // Split command and file up into tokens
    const char *delim1 = " ";
    const char *delim2 = " \n";
    char *command = strtok(buffer, delim1);
    char *file = strtok(NULL, delim2);

    
    if (strcmp("get", command) == 0) {
        int write_fd = 1;
    } else if(strcmp("set", command) == 0) {
        int read_fd = 0;
    } else {
        write(2, invalid, strlen(invalid));
        return 1;
    }

    if (strlen(file) > PATH_MAX) {
        write(2, invalid, strlen(invalid));
        return 1;
    }


    if (bytes_read == -1) {
        write(2, "Operation Failed\n", strlen("Operation Failed\n"));
        return 1;
    }


    //int in_fd;  // fd for which std to 
    //int out_fd; // fd 
    if (strcmp(command, "get") == 0) {

    }
   // int fd = open(file, O_RDWR);

}

    /*
    bytes_read = 0;


    do {
        bytes_read = read(fd, buffer, BUFFER_SIZE);

        if (bytes_read < 0) {
            write(2, "Operation Failed\n", strlen("Operation Failed\n"));
            return 1;
        } else if (bytes_read > 0) {
            ssize_t bytes_written = 0;

           // do {
           //     ssize_t bytes = write()
           // }
        }
    }

}
*/







    /*

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
        while (bytes_read > 0 && writeVal > -1) {
            bytes_read = read(fd, buffer, 4096);
            writeVal = write(1, buffer, bytes_read);
        }

        close(fd); // This was moved up

        if (bytes_read == -1 || writeVal == -1) { // If write fails
            write(2, "Operation Failed\n", strlen("Operation Failed\n"));
            return 1;
        }

    } else if (strcmp(command, "set") == 0) {
        //if (fd == -1) {
        //fd = open(file, S_IRWXU | O_RDWR | O_TRUNC | O_CREAT);
        fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
        // while (bytes_read > 0 && writeVal > -1) {
        while (bytes_read >= 0) {
            bytes_read = read(0, buffer, 4096);
            writeVal = write(fd, buffer, bytes_read);
        }

        return 0;
        //}
    } else {
        write(2, "Invalid Command\n", strlen("Invalid Command\n"));
        return 1;
    }
    return 0;
}
*/
