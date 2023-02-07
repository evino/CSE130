#pragma once

#include <stdlib.h>
#include <string.h>

#include "helpers.h"
#include "asgn2_helper_funcs.h"

#define BUFF_SIZE 4096

enum status_codes {
    OK = 200,
    Created = 201,
    BAD_REQUEST = 400,
    Forbidden = 403,
    Not_Found = 404,
    Server_Error = 500,
    Not_Implemented = 501,
    Version_Not_Supported = 505
};

typedef struct {
    char buf[BUFF_SIZE + 1];
    char *method;
    char *URI;
    char *version;
    char *request;
    char *key;
    char *value;
    int length;
    char *header_field;
    char request_line[BUFF_SIZE + 1];
    int status;
    int client_fd;
    int server_fd;
    int file_size;
    int bytes_read;
    char *phrase;
} Command;

//Command* request_parse(Command *com);
void request_parse(Command *com);

void header_parse(Command *com);

void content_len(Command *com);

// Returns status code
int status_return();
