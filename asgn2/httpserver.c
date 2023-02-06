#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <stdio.h>

#include "asgn2_helper_funcs.h"
#include "helpers.h"
#include "parse.h"

//#define BUFF_SIZE 4096
//char buf[BUFF_SIZE + 1];

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
    if (sock_fd == -1) {
        return (invalid_port());
    }

    int listen_fd;
    // Maybe do-while listen_fd > 0???
    int bytes_read;
    while (1) {
		write(sock_fd, "top\n", strlen("top\n"));

        listen_fd = listener_accept(&sock);

        if (listen_fd != -1) {
            bytes_read = read_until(listen_fd, command.buf, BUFF_SIZE, "\r\n\r\n");
            command.buf[BUFF_SIZE] = 0;
            command.request_line = command.buf;
            printf("db: %d\n", bytes_read);


            /*
			// FIGURE OUT WHAT WILL NEED TO HAPPEN HERE

			if (bytes_read == -1) { // RETURN internal server error code here
				return 1;
			}
			*/

            //printf("%s\n", buf);
            //write(listen_fd, buf, strlen(buf));
            //printf("%zd\n", write_all(listen_fd, command.buf, BUFF_SIZE));
            // want to send thus buffer to a seperate file that
            // parses using regex

            printf("%d\n", bytes_read);

            printf("buf, %s\n", command.buf);
            //command = *(request_parse(&command));
            
            request_parse(&command);
                        printf("db buf,\n%s\n", command.buf);

                //printf("msg is %s\n", command.msg);
            content_len(&command);

            printf("DB: %s\n", command.header_field);
            printf("DB: %s\n", command.method);

            printf("len is %d\n", command.length);  // THIS WILL ERROR IF "Content-Length" isn't present
            //header_parse(&command);


            printf("TEST: %s\n", command.request_line);
			// READ message body
            if (strcmp(command.method, "PUT") == 0) {
                //int msg_read = read_until(listen_fd, command.buf, command.length, NULL);
                if (bytes_read < BUFF_SIZE) {  // We know it reached end of file
                    command.msg = command.msg + 4;
                    //const char delim[] = "\r\n\r\n";
                    //char *token = strtok(command.buf, "\r\n\r\n");
                    //token = strtok(NULL, delim);
                    //printf("buf, %s\n", command.buf);
                    //char *msg = strstr(command.buf, "\r\n\r\n");
                    write(sock_fd, command.msg, strlen(command.msg));
                    //printf("msg = %s\n", token);
                    //write_all(sock_fd, msg + 4, BUFF_SIZE);
                }
            }
			
			
			
			
			// CLOSES CLIENT SIDE AT END
			int status_code = status_return();
			switch (status_code)
			{
			case (BAD_REQUEST):
				write(listen_fd, "BAD REQUEST\n", strlen("BAD REQUEST\n"));
				break;
			
			default:
				break;
			}
			
			close(listen_fd);
            // write(listen_fd, "\ndone\r\n", strlen("\ndone\r\n")); // returning once timed out
        }
    }

    printf("%d", listen_fd);

    return 0;
}
