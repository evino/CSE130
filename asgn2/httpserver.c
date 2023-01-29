#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

#include "asgn2_helper_funcs.h"
#include "helpers.h"

#define BUFF_SIZE 4096
char buff[BUFF_SIZE + 1];

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
	while(1) {
		listen_fd = listener_accept(&sock);


	}	

	printf("%d", listen_fd);

	



	return 0;
}
