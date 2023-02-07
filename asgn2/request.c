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
        bad_req(com);
        return;
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
    } else if (strcmp("PUT", com->method) == 0) {
        content_len(com);
        int fd = open(com->URI, O_RDWR | O_TRUNC);
        if (fd == -1) {
            fd = creat(com->URI, 0777);
            com->phrase = "Created";
            com->status = Created;
        } else {
            com->phrase = "OK";
            com->status = OK;
        }

        put_response(com, fd);
        close(fd);
        return;

    } else {
        com->status = Not_Implemented;
        not_imp(com);
        return;
    }
}
