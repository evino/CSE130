#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <stdio.h>

#include "asgn2_helper_funcs.h"
#include "helpers.h"
#include "parse.h"
#include "request.h"

int main(int argc, char **argv) {
    Command command = { 0 };
    if (argc != 2) {
        //return (invalid_port());
        char *usage = "usage: ./httpserver <port>\n";
        write(2, usage, strlen(usage));
        return 1;
    }

    int port = atoi(argv[1]);
    if (port < 1 || port > 65535) {
        return (invalid_port());
    }

    Listener_Socket sock;

    int sock_fd = listener_init(&sock, port);
    command.server_fd = sock_fd;
    if (sock_fd == -1) {
        return (invalid_port());
    }

    int listen_fd;
    int bytes_read;
    while (1) {

        listen_fd = listener_accept(&sock);
        command.client_fd = listen_fd;
        if (listen_fd != -1) {
            bytes_read
                = read_until(listen_fd, command.buf, BUFF_SIZE, "\r\n\r\n"); // ADD ERROR CHECK HERE

            command.buf[BUFF_SIZE] = 0;
            command.bytes_read = bytes_read;

            strcpy(command.request_line, command.buf);

            request_parse(&command);
            request_handler(&command);

            close(listen_fd);
        }
    }

    return 0;
}
