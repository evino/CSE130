#include "response.h"

void bad_req(Command *com) {
    write_all(com->client_fd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n", strlen("HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n"));
}

void not_imp(Command *com) {
    write_all(com->client_fd, "HTTP/1.1 501 Not Implemented\r\nContent-Length: 16\r\n\r\nNot Implemented\n", strlen("HTTP/1.1 501 Not Implemented\r\nContent-Length: 16\r\n\r\nNot Implemented\n"));
}
