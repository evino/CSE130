// Asgn 2: A simple HTTP server.
// By: Eugene Chou
//     Andrew Quinn
//     Brian Zhao

#include "asgn2_helper_funcs.h"
#include "connection.h"
#include "debug.h"
#include "response.h"
#include "request.h"
#include "queue.h"

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/file.h>

#include <pthread.h>

void handle_connection(int);

void handle_get(conn_t *);
void handle_put(conn_t *);
void handle_unsupported(conn_t *);

void *worker(void *);

void audit(const char *oper, char *uri, uint16_t status_code, char *req_id);


int main(int argc, char **argv) {
    if (argc < 2) {
        warnx("wrong arguments: %s port_num", argv[0]);
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr = NULL;
    size_t port = (size_t) strtoull(argv[1], &endptr, 10);
    if (endptr && *endptr != '\0') {
        warnx("invalid port number: %s", argv[1]);
        return EXIT_FAILURE;
    }

    if (port < 1 || port > 65535) {
        fprintf(stderr, "Invalid Port\n");
        return 1;
    }


    signal(SIGPIPE, SIG_IGN);
    Listener_Socket sock;
    listener_init(&sock, port);


    // Add in optional arg
    uintptr_t thread_num = 4; // By default
    queue_t *queue = queue_new(thread_num);


    //pthread_t threads[thread_num];
    pthread_t *threadArr = malloc(sizeof(pthread_t) * thread_num);

    for (uintptr_t t = 0; t < thread_num; t++) {
        pthread_create(&(threadArr[t]), NULL, worker, (void *) queue);                                                                                                                   
    }

    while (1) {
        uintptr_t connfd = listener_accept(&sock);

        // MIGHT NEED TO ADD ERROR CHECK FOR VALID CONN
        queue_push(queue, (void *) connfd);
        // printf("GOing to call worker()\n");
        // handle_connection(connfd);
        //worker(queue);

        printf("SERVER DB: CLOSING CLIENT\n"); // DEBUG
        write(connfd, "About to close connection\n", strlen("About to close connection\n"));  // DEBUG
        // close(connfd);  WORKER CAN CLOSE
    }


    queue_delete(&queue);
    free(threadArr);
    threadArr = NULL;

    return EXIT_SUCCESS;
}

void *worker(void *q) {
    printf("In worker\n");
    q = (queue_t *) q;
    while (1) {
        // printf("DB1\n");
        void *connfd = NULL;
        queue_pop(q, (void *) &connfd);
        
        handle_connection((uintptr_t) connfd);
        // printf("after handle\n");

        close((uintptr_t) connfd);
    }

    return NULL;
}




void handle_connection(int connfd) {

    conn_t *conn = conn_new(connfd);

    const Response_t *res = conn_parse(conn);

    // const Request_t *request = conn_get_request(conn);
    // const char *oper = request_get_str(req);  // Operation

    // flock(2, LOCK_EX);
    //fprintf(stderr, "DEBUG: %s, %s, %hu\r\n", oper, conn_get_uri(conn), response_get_code(res));
    // fprintf(stderr, "DEBUG: %s\n", conn_get_header(conn, "Request-Id"));
    // flock(2, LOCK_UN);

    char *uri = conn_get_uri(conn);

    
    dprintf(connfd, "db1\n");


    if (res != NULL) {
        const Request_t *request = conn_get_request(conn);
        const char *oper = request_get_str(request);  // Operation
        // char *uri = conn_get_uri(conn);

        fprintf(stderr, "IN NULL CASE\n");
        audit(oper, uri, response_get_code(&RESPONSE_NOT_IMPLEMENTED), conn_get_header(conn, "Request-Id"));
        
        // Original
        conn_send_response(conn, res);
        dprintf(connfd, "db2\n");
    } else {
        debug("%s", conn_str(conn));
        const Request_t *req = conn_get_request(conn);
        if (req == &REQUEST_GET) {
            handle_get(conn);
        } else if (req == &REQUEST_PUT) {
            printf("IS PUT REQ\n");
            handle_put(conn);  // connfd is for DEBUG!!!!
            dprintf(connfd, "db3\n");
        } else {
            handle_unsupported(conn);
        }
    }

    conn_delete(&conn);
}

void handle_get(conn_t *conn) {

    char *uri = conn_get_uri(conn);
    debug("GET request not implemented. But, we want to get %s", uri);

    // What are the steps in here?

    // 1. Open the file.
    // If  open it returns < 0, then use the result appropriately
    //   a. Cannot access -- use RESPONSE_FORBIDDEN
    //   b. Cannot find the file -- use RESPONSE_NOT_FOUND
    //   c. other error? -- use RESPONSE_INTERNAL_SERVER_ERROR
    // (hint: check errno for these cases)!

    // 2. Get the size of the file.
    // (hint: checkout the function fstat)!

    // Get the size of the file.

    // 3. Check if the file is a directory, because directories *will*
    // open, but are not valid.
    // (hint: checkout the macro "S_IFDIR", which you can use after you call fstat!)


    // 4. Send the file
    // (hint: checkout the conn_send_file function!)

}

void handle_unsupported(conn_t *conn) {
    debug("handling unsupported request");


    const Request_t *req = conn_get_request(conn);

    // send responses
    char *uri = conn_get_uri(conn);
    const char *oper = request_get_str(req);

    // const Response_t *res = conn_parse(conn);


    
    //uint16_t statusCode = response_get_code(res);

    audit(oper, uri, response_get_code(&RESPONSE_NOT_IMPLEMENTED), conn_get_header(conn, "Request-Id"));


    conn_send_response(conn, &RESPONSE_NOT_IMPLEMENTED);
}

void handle_put(conn_t *conn) {  // connfd is for DEBUG!!!!

    char *uri = conn_get_uri(conn);

    const Response_t *res = NULL;
    debug("handling put request for %s", uri);

    // Check if file already exists before opening it.
    bool existed = access(uri, F_OK) == 0;
    debug("%s existed? %d", uri, existed);

    // Open the file..
    int fd = open(uri, O_CREAT | O_TRUNC | O_WRONLY, 0600);
    if (fd < 0) {
        debug("%s: %d", uri, errno);
        if (errno == EACCES || errno == EISDIR || errno == ENOENT) {
            res = &RESPONSE_FORBIDDEN;
            goto out;
        } else {
            res = &RESPONSE_INTERNAL_SERVER_ERROR;
            goto out;
        }
    }

    res = conn_recv_file(conn, fd);

    if (res == NULL && existed) {
        res = &RESPONSE_OK;
    } else if (res == NULL && !existed) {
        res = &RESPONSE_CREATED;
    }

    const Request_t *req = conn_get_request(conn);
    const char *oper = request_get_str(req);
    uint16_t statusCode = response_get_code(res);
    char *reqID = conn_get_header(conn, "Request-Id");

    audit(oper, uri, statusCode, reqID);

    close(fd);

out:
    conn_send_response(conn, res);

    //fprintf(stderr, "CODE: %hu\n", response_get_code(res));

}

void audit(const char *oper, char *uri, uint16_t status_code, char *req_id) {
    flock(2, LOCK_EX);
    if (req_id  == NULL) {
        fprintf(stderr, "ITSA NULL\n");
        fprintf(stderr, "AUDIT LOG: %s,/%s,%hu,%s\n", oper, uri, status_code, "0");
    } else {
        fprintf(stderr, "AUDIT LOG: %s,/%s,%hu,%s\n", oper, uri, status_code, req_id);
    }
    flock(2, LOCK_UN);
}
