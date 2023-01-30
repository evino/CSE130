#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <stdio.h>

#include "asgn2_helper_funcs.h"
#include "helpers.h"

#define BUFF_SIZE 4096
char buf[BUFF_SIZE + 1];

int main(int argc, char **argv) {
	if (argc != 2) {
		return (invalid_port());
	}

	int port = atoi(argv[1]);
	if (port < 1 || port > 65535) {
		return (invalid_port());
	}

	Listener_Socket sock;

	int sock_fd = listener_init(&sock, port);
	if (sock_fd == -1) {
		return (invalid_port());
	}

	int listen_fd;
	// Maybe do-while listen_fd > 0???
	int bytes_read;
	while(1) {
		listen_fd = listener_accept(&sock);
        if (listen_fd != -1) {
			// do {
			// 	bytes_read = read_until(listen_fd, buf, 4, NULL);
			// } while (bytes_read > 0);
			bytes_read = read_until(listen_fd, buf, BUFF_SIZE, "\n");

/*
			if (bytes_read == -1) {
				return 1;
			}
*/
			//printf("%s\n", buf);
			write(listen_fd, buf, strlen(buf));
			printf("%d\n", bytes_read);


			write(listen_fd, "done\r\n", strlen("done\r\n")); // returning once timed out
        }

	}	

	printf("%d", listen_fd);

	



	return 0;
}
