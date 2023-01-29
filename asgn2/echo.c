#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "asgn2_helper_funcs.h"

#define BUF_SIZE 4096

int main(int argc, char **argv) {
    char buff[BUF_SIZE + 1];
    if (argc != 2) {
        write(2, "Invalid Command Arg\n", strlen("Invalid Command Arg\n"));
        return 1;
    }

    int port = atoi(argv[1]);

    if (port < 1 || port > 65535) {
        write(2, "Invalid Port\n", strlen("Invalid Port\n"));
        return 1;
    }

    Listener_Socket sock;

    int sock_fd = listener_init(&sock, port);
    if (sock_fd == -1) {
        write(2, "Invalid Port\n", strlen("Invalid Port\n"));
        return 1;
        //write(2, "Could not establish a new connection\n", strlen( "Could not establish a new connection\n"));
    }

    int bytes_read = 0;
    // char *byteStr;
    while (1) {
        int listen_fd = listener_accept(&sock);

        if (listen_fd > 0) {
            // bytes_read = bytes_read + read(listen_fd, buff, BUF_SIZE);
            do {
                bytes_read = read(listen_fd, buff, 4);
                printf("%d\n", bytes_read);

            } while (bytes_read > 0);
            //byteStr = itoa(bytes_read);
            //write(1, byteStr, strlen(byteStr));
        }
        close(listen_fd);
    }

    return 0;
}
