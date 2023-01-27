#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "asgn2_helper_funcs.h"


int main(int argc, char **argv) {
	if (argc != 2) {
		write(2, "Invalid Command Arg\n", strlen("Invalid Command Arg\n"));
		return 1;
	}

	int port = atoi(argv[1]);

	Listener_Socket sock;

	int sock_fd = listener_init(&sock, port);
	if (sock_fd == -1) {
		write(2, "Could not establish a new connection\n", strlen( "Could not establish a new connection\n"));
	}
	return 0;
}
