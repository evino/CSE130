#include "request.h"
#include "response.h"



void request_handler(Command *com) {

    if (com->status == BAD_REQUEST) {
        //write_all(client_fd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n", strlen("HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n"));
        bad_req(com);
        return;
        //close(com->client_fd);
    }

    if (strcmp("GET", com->method) == 0) {

    } else if (strcmp("PUT", com->method) == 0) {

    } else {
        com->status = Not_Implemented;
        not_imp(com);
        //status_phrase = "Not Implemented\r\n";
    }
}
