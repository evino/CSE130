#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096

int invalid() {
    write(2, "Invalid Command\n", strlen("Invalid Command\n"));
    return 1;
}

int main() {
    char buffer[BUFFER_SIZE] = ""; // Might need to initialize to silence valgrind error

    // char *invalid = "Invalid Command\n";

    // read command and file from STDIN
    // Can read one byte at a time, and loop till there is a newline (in buffer)
    // int bytes_read = read(0, buffer, BUFFER_SIZE);
    int bytes_read = 0;

    int byte_count = 0;
    do {
        bytes_read = read(0, buffer + byte_count, 1);
        byte_count++;
    } while (bytes_read > 0 && strstr(buffer, "\n") == NULL);

    if (bytes_read == -1) { // Make sure read didn't fail
        write(2, "Operation Failed\n", strlen("Operation Failed\n"));
        return 1;
    }

    // Split command and file up into tokens
    const char *delim1 = " ";
    const char *delim2 = "\n";
    char *command = strtok(buffer, delim1);
    char *file = strtok(NULL, delim2);

    // Make sure some location was passed in
    if (file == NULL) {
        return invalid();
    }

    // Make sure location name is valid
    if (strstr(file, " ") != NULL || strstr(file, "\n") != NULL) {
        return invalid();
    }

    // printf("DB1\n");
    struct stat fileCheck = { 0 };
    stat(file, &fileCheck);
    if (S_ISDIR(fileCheck.st_mode) != 0) { // File is a directory, therefore not valid
        return invalid();
    }
    // printf("DB2\n");

    // If file is blank
    // if (strcmp(file, "") == 0) {
    //     return invalid();
    // }

    int write_fd = 999;
    int read_fd = 999;
    if (strcmp("get", command) == 0) {
        write_fd = 1;
    } else if (strcmp("set", command) == 0) {
        read_fd = 0;
    } else {
        return invalid();
        // write(2, invalid, strlen(invalid));
        // return 1;
    }

    if (strlen(file) > PATH_MAX) {
        return invalid();
    }

    if (bytes_read == -1) {
        write(2, "Operation Failed\n", strlen("Operation Failed\n"));
        return 1;
    }

    // Make sure file is closed
    int fd = open(file, O_RDWR);
    // printf("DB\n");
    if (fd == -1 && write_fd == 1) { // File does not exist
        return invalid();
        //write(2, invalid, strlen(invalid));
        //return 1;
    } else if (write_fd == 1 && fd > -1) {
        read_fd = fd;
    } else if (read_fd == 0) { // If command is "set"
        // if (unlink())
        // open(file, O_CREAT O_RDWR | O_TRUNC, 0777);
        //close(fd);
        //write_fd = creat(file, 0777);
        write_fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0777);
        fd = write_fd;
        // printf("right before check\n");
        // printf("write_fd: %d\n", write_fd);
        if (write_fd == -1) { // Make sure creat worked
            write(2, "Operation Failed\n", strlen("Operation Failed\n"));
            return 1;
        }
    }

    bytes_read = 0;
    do {
        bytes_read = read(read_fd, buffer, BUFFER_SIZE);

        if (bytes_read < 0) {
            write(2, "Operation Failed\n", strlen("Operation Failed\n"));
            return 1;
        } else if (bytes_read > 0) {
            int bytes_written = 0;
            do {
                int bytes = write(write_fd, buffer + bytes_written, bytes_read - bytes_written);

                if (bytes <= 0) {
                    write(2, "Operation Failed\n", strlen("Operation Failed\n"));
                    return 1;
                }

                bytes_written += bytes;

            } while (bytes_written < bytes_read);
        }
    } while (bytes_read > 0);

    //printf("%d", read_fd);

    // MAKE SURE TO CLOSE PROPER FILES, AND CHECK IT!!!

    if (close(fd) == -1) { // THIS IF IS CAUSING THE FAIL WHEN CALLING SET ON NEW FILE
        write(2, "Operation Failed\n", strlen("Operation Failed\n")); // ADD DB HERE IF NEEDED
        return 1;
    }

    if (read_fd == 0) {
        write(1, "OK\n", strlen("OK\n"));
    }

    return 0;
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
