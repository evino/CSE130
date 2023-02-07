#include "request.h"
#include "response.h"

int file_check(Command *com) {
    int fd = open(com->URI, O_RDONLY);

    // Checks if file exists
    if (fd == -1) {
        return -1;
    }
    struct stat fileCheck = { 0 };
    fstat(fd, &fileCheck);

    if (S_ISREG(fileCheck.st_mode) == 0) {
        return -2;
    }

    com->file_size = fileCheck.st_size;

    return fd;
}

void request_handler(Command *com) {

    if (com->status == BAD_REQUEST) {
        //write_all(client_fd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n", strlen("HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n"));
        bad_req(com);
        return;
        //close(com->client_fd);
    }

    if (strcmp("HTTP/1.1", com->version) != 0) {
        com->status = Version_Not_Supported;
        not_sup(com);
        return;
    }

    if (strcmp("GET", com->method) == 0) {
        int fd = file_check(com);
        if (fd == -1) {
            not_found(com);
            return;
        } else if (fd == -2) {
            forbid(com);
            return;
        }
        com->status = 200;
        get_response(com, fd);
        close(fd);
        return;
        // int passed;
        // do {
        //     passed = pass_bytes(fd, com->client_fd, BUFF_SIZE);
        // } while (passed == BUFF_SIZE);
    } else if (strcmp("PUT", com->method) == 0) {
        // content_len(com);
        int fd = open(com->URI, O_RDWR | O_TRUNC);
        if (fd == -1) {
            //fd = creat(com->URI, S_IRWXG)
            fd = creat(
                com->URI, 0777); // Let's see if if this gets rid of file being seen as executable
            com->phrase = "Created";
            com->status = Created;
        } else {
            com->phrase = "OK";
            com->status = OK;
        }

        put_response(com, fd);
        close(fd);
        return;

        // write_all(fd, strstr(com->buf, "\r\n\r\n") + 4, (com->buf + com->bytes_read) - strstr(com->buf, "\r\n\r\n") + 4);
        // int passed;
        // do {
        //     passed = pass_bytes(com->client_fd, fd, BUFF_SIZE);
        // } while (passed == BUFF_SIZE);

        //write(com->client_fd, phrase, strlen(phrase));
    } else {
        com->status = Not_Implemented;
        not_imp(com);
        return;
        //status_phrase = "Not Implemented\r\n";
    }
}
