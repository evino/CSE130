// Evin Odisho
// CSE-130 Assignment 4
// Multi-threaded HTTP-Server
// Built on top of:
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
#include <assert.h>

#include <sys/stat.h>
#include <sys/file.h>

#include <pthread.h>

void handle_connection(int);

void handle_get(conn_t *);
void handle_put(conn_t *);
void handle_unsupported(conn_t *);

void *worker(void *);

void audit(const char *oper, char *uri, uint16_t status_code, char *req_id);

pthread_mutex_t file_mutex;

int main(int argc, char **argv) {
    if (argc < 2) {
        warnx("wrong arguments: %s port_num", argv[0]);
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int thread_num = getopt(argc, argv, "t:");
    if (thread_num == -1) {
        thread_num = 4;
    } else {
        thread_num = atoi(optarg);
    }

    char *endptr = NULL;
    size_t port = (size_t) strtoull(argv[argc - 1], &endptr, 10);
    if (endptr && *endptr != '\0') {
        warnx("invalid port number: %s", argv[argc - 1]);
        return EXIT_FAILURE;
    }

    if (port < 1 || port > 65535) {
        fprintf(stderr, "Invalid Port\n");
        return 1;
    }

    signal(SIGPIPE, SIG_IGN);
    Listener_Socket sock;
    listener_init(&sock, port);

    assert(!(pthread_mutex_init(&file_mutex, NULL)));

    uintptr_t threads = (uintptr_t) thread_num;

    queue_t *queue = queue_new(threads);
    pthread_t *threadArr = malloc(sizeof(pthread_t) * threads);

    for (uintptr_t i = 0; i < threads; i++) {
        pthread_create(&(threadArr[i]), NULL, worker, (void *) queue);
    }

    while (1) {
        uintptr_t connfd = listener_accept(&sock);
        queue_push(queue, (void *) connfd);
    }

    queue_delete(&queue);
    free(threadArr);
    threadArr = NULL;

    pthread_mutex_destroy(&file_mutex);

    return EXIT_SUCCESS;
}

void *worker(void *q) {
    q = (queue_t *) q;
    while (1) {
        void *connfd = NULL;
        queue_pop(q, (void *) &connfd);
        handle_connection((uintptr_t) connfd);
        close((uintptr_t) connfd);
    }
    return NULL;
}

void handle_connection(int connfd) {

    conn_t *conn = conn_new(connfd);
    const Response_t *res = conn_parse(conn);
    char *uri = conn_get_uri(conn);

    if (res != NULL) {
        const Request_t *request = conn_get_request(conn);
        const char *oper = request_get_str(request); // Operation
        audit(oper, uri, response_get_code(&RESPONSE_NOT_IMPLEMENTED),
            conn_get_header(conn, "Request-Id"));
        conn_send_response(conn, res);
    } else {
        debug("%s", conn_str(conn));
        const Request_t *req = conn_get_request(conn);
        if (req == &REQUEST_GET) {
            handle_get(conn);
        } else if (req == &REQUEST_PUT) {
            handle_put(conn);
        } else {
            handle_unsupported(conn);
        }
    }

    conn_delete(&conn);
}

void handle_get(conn_t *conn) {

    char *uri = conn_get_uri(conn);
    debug("handling get request for %s", uri);

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

    const Response_t *res = NULL;
    debug("handling put request for %s", uri);

    // bool existed = access(uri, F_OK) == 0;
    // debug("%s existed? %d", uri, existed);

    // Lock the mutex to ensure only
    // one file can be opened at a time.
    pthread_mutex_lock(&file_mutex);
    int fd = open(uri, O_RDONLY);

    flock(fd, LOCK_SH);
    pthread_mutex_unlock(&file_mutex);

    struct stat fileCheck = { 0 };
    stat(uri, &fileCheck);
    int fileSize = fileCheck.st_size;

    if (fd < 0) {
        debug("ERROR: %s: %d", uri, errno);

        if (errno == EACCES) {
            res = &RESPONSE_FORBIDDEN;
            goto outBad;
        } else if (errno == ENOENT) {
            res = &RESPONSE_NOT_FOUND;
            goto outBad;
        } else {
            res = &RESPONSE_INTERNAL_SERVER_ERROR;
            goto outBad;
        }
    }

    if (S_ISDIR(fileCheck.st_mode) != 0) {
        res = &RESPONSE_FORBIDDEN;
        goto outBad;
    }

    if (res == NULL) {
        res = &RESPONSE_OK;
        goto outGood;
    }

outBad:
    conn_send_response(conn, res);

outGood:
    if (res == &RESPONSE_OK) {
        conn_send_file(conn, fd, fileSize);
    }

    uint16_t statusCode = response_get_code(res);
    const char *oper = "GET";
    char *reqID = conn_get_header(conn, "Request-Id");

    audit(oper, uri, statusCode, reqID);

    flock(fd, LOCK_UN);
    close(fd);
    return;
}

void handle_unsupported(conn_t *conn) {
    debug("handling unsupported request");

    const Request_t *req = conn_get_request(conn);

    // send responses
    char *uri = conn_get_uri(conn);
    const char *oper = request_get_str(req);

    audit(oper, uri, response_get_code(&RESPONSE_NOT_IMPLEMENTED),
        conn_get_header(conn, "Request-Id"));

    conn_send_response(conn, &RESPONSE_NOT_IMPLEMENTED);
}

void handle_put(conn_t *conn) { // connfd is for DEBUG!!!!
    char *uri = conn_get_uri(conn);
    char *reqID = conn_get_header(conn, "Request-Id");

    const Response_t *res = NULL;
    debug("handling put request for %s", uri);

    // Check if file already exists before opening it.
    bool existed = access(uri, F_OK) == 0;
    debug("%s existed? %d", uri, existed);

    // Mutex is locked so only one file
    // can be opened at a time, and truncate
    // happens only after exclusive lock is
    // placed on it to ensure it's atomic.
    pthread_mutex_lock(&file_mutex);
    int fd = open(uri, O_CREAT | O_WRONLY, 0600);
    flock(fd, LOCK_EX);

    pthread_mutex_unlock(&file_mutex);

    int ftrunc = 0;
    if (existed) {
        ftrunc = ftruncate(fd, 0);
    }

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

    if (ftrunc < 0) {
        res = &RESPONSE_INTERNAL_SERVER_ERROR;
        goto out;
    }

    res = conn_recv_file(conn, fd);

    if (res == NULL && existed) {
        res = &RESPONSE_OK;
    } else if (res == NULL && !existed) {
        res = &RESPONSE_CREATED;
    }

out:
    audit("PUT", uri, response_get_code(res), reqID);
    conn_send_response(conn, res);
    flock(fd, LOCK_UN);
    close(fd);

    return;
}

void audit(const char *oper, char *uri, uint16_t status_code, char *req_id) {
    if (req_id == NULL) {
        fprintf(stderr, "%s,/%s,%hu,%s\n", oper, uri, status_code, "0");
    } else {
        fprintf(stderr, "%s,/%s,%hu,%s\n", oper, uri, status_code, req_id);
    }
}
