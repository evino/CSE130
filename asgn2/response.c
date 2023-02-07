#include "response.h"

void bad_req(Command *com) {
    com->status = BAD_REQUEST;
    write_all(com->client_fd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n",
        strlen("HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n"));
}

void not_imp(Command *com) {
    com->status = Not_Implemented;
    write_all(com->client_fd,
        "HTTP/1.1 501 Not Implemented\r\nContent-Length: 16\r\n\r\nNot Implemented\n",
        strlen("HTTP/1.1 501 Not Implemented\r\nContent-Length: 16\r\n\r\nNot Implemented\n"));
}

void not_sup(Command *com) {
    write_all(com->client_fd,
        "HTTP/1.1 505 Version Not Supported\r\nContent-Length: 22\r\n\r\nVersion Not Supported\n",
        strlen("HTTP/1.1 501 Version Not Supported\r\nContent-Length: 22\r\n\r\nVersion Not "
               "Supported\n"));
}

void not_found(Command *com) {
    write_all(com->client_fd, "HTTP/1.1 404 Not Found\r\nContent-Length: 10\r\n\r\nNot Found\n",
        strlen("HTTP/1.1 404 Not Found\r\nContent-Length: 10\r\n\r\nNot Found\n"));
}

void forbid(Command *com) {
    write_all(com->client_fd, "HTTP/1.1 403 Forbidden\r\nContent-Length: 10\r\n\r\nForbidden\n",
        strlen("HTTP/1.1 403 Forbidden\r\nContent-Length: 10\r\n\r\nForbidden\n"));
}

void get_response(Command *com, int fd) {
    char response[BUFF_SIZE];

    int spf = sprintf(response, "%s %d OK\r\nContent-Length: %d\r\n\r\n", com->version, com->status,
        com->file_size);
    if (spf < 0) { // Internal error with sprintf() occured
        write_all(com->client_fd,
            "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal Server "
            "Error\n",
            strlen("HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal "
                   "Server Error\n"));
        return;
    }
    write_all(com->client_fd, response, strlen(response));
    int passed;
    do {
        passed = pass_bytes(fd, com->client_fd, BUFF_SIZE);
    } while (passed == BUFF_SIZE);

    return;
}

void put_response(Command *com, int fd) {

    write_all(fd, strstr(com->buf, "\r\n\r\n") + 4, com->length);

    int passed;
    do {
        passed = pass_bytes(com->client_fd, fd, BUFF_SIZE);
    } while (passed == BUFF_SIZE);

    char response[BUFF_SIZE];
    int spf = sprintf(response, "%s %d %s\r\nContent-Length: %lu\r\n\r\n%s\n", com->version,
        com->status, com->phrase, strlen(com->phrase) + 1, com->phrase);
    if (spf < 0) {
        write_all(com->client_fd,
            "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal Server "
            "Error\n",
            strlen("HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal "
                   "Server Error\n"));
        return;
    }
    write_all(com->client_fd, response, strlen(response));

    return;
}
