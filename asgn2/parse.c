
#include <regex.h>
#include <assert.h>
#include <stdbool.h>


#include "parse.h"
#include "helpers.h"

// FOR DB
#include <stdio.h>

//#define REQUEST_REGEX "^([a-zA-Z]{1,8}) /([a-zA-Z0-9._]{1,63}) (HTTP/[0-9].[0-9])\r\n"
#define REQUEST_REGEX "^([a-zA-Z]{1,8}) /([a-zA-Z0-9.-]{1,63}) (HTTP/[0-9].[0-9])\r\n(([a-zA-Z0-9.-]{1,128}: [\x20-\x7F]{0,128}\r\n)*)\r\n"

#define HEADER_REGEX "\r\n(([a-zA-Z0-9.-]{1,128}): ([\x20-\x7F]{0,128})\r\n*)"

#define CONTENT_LEN "(Content-Length): ([0-9]{1,128})"

int status = 0; // WILL HAVE TO ASSIGN FOR EACH POSSIBLE STATUS
Command* request_parse(Command *com) {
    regex_t re;
    regmatch_t matches[5];
    int rc;

    rc = regcomp(&re, REQUEST_REGEX, REG_EXTENDED);
    assert(!rc); // MAY NEED INTERNAL SERVER ERROR HERE

   // bool badRequest = false;

    rc = regexec(&re, (char *) com->buf, 5, matches, 0);
    if (rc == 0) {
        com->request_line = com->buf;

        com->method = com->buf + matches[1].rm_so;
        com->method[matches[1].rm_eo - matches[1].rm_so] = '\0';

        com->URI = com->buf + matches[2].rm_so;
        com->URI[matches[2].rm_eo - matches[2].rm_so] = '\0';

        com->version = com->buf + matches[3].rm_so;
        com->version[matches[3].rm_eo - matches[3].rm_so] = '\0';

        com->header_field = com->buf + matches[4].rm_so;
        com->header_field[matches[4].rm_eo - matches[4].rm_so] = '\0';

        status = 200; // CHANGE THIS LATER!!

        
        //   com->method = &REQUEST_REGEX[matches[1].rm_so];// - matches[1].rm_so;
        //com->method[matches[1].rm_eo] = '\0';  // NEED TO FIGURE OUT WHY method is NULL
    } else {
        printf("NOOOOOOO MATCHOOOOO\n");  // BAD REQUEST WOULD GO HERE
        //badRequest = true;
        //com->status = 400;
        //status = status_codes.BAD_REQUEST;
        status = BAD_REQUEST;
    }

    regfree(&re);
    if (status == BAD_REQUEST) {
        printf("SHOULD PRINT A BAD REQUEST here\n");
    } else {
        printf("method: %s\n", com->method);
        printf("URI: %s\n", com->URI);
        printf("version: %s\n", com->version);
        printf("header: %s\n", com->header_field);
    }


    //printf("db: %s\n", matches[0]);
    // DEBUG PRINTS

    return com;
}
// CALL REGFREE


void header_parse(Command *com) {
    regex_t re;
    regmatch_t matches[3];
    int rc;

    rc = regcomp(&re, HEADER_REGEX, REG_EXTENDED);
    assert(!rc);

    rc = regexec(&re, (char *) com->buf, 3, matches, 0);

    if (rc == 0) {
        com->header_field = com->buf;

        com->key = com->buf + matches[1].rm_so;
        com->key[matches[1].rm_eo - matches[1].rm_so] = '\0';

        com->value = com->buf + matches[2].rm_so;
        com->value[matches[2].rm_eo - matches[2].rm_so] = '\0';
    } else {
        printf("DB, header no match for now\n");
    }


    regfree(&re);
    printf("key: %s\n", com->key);
    printf("val: %s\n", com->value);
}

void content_len(Command *com) {
    regex_t re;
    regmatch_t matches[3];
    int rc;

    rc = regcomp(&re, CONTENT_LEN, REG_EXTENDED);
    assert(!rc);

    rc = regexec(&re, (char *) com->header_field, 3, matches, 0);
    if (rc == 0) {
        com->key = com->header_field + matches[1].rm_so;
        com->key[matches[1].rm_eo - matches[1].rm_so] = '\0';

        com->value = com->header_field + matches[2].rm_so;
        com->value[matches[2].rm_eo - matches[2].rm_so] = '\0';
    } else {
        printf("ERR\n");
    }


    com->length = atoi(com->value);
    //int length = atoi(com->value);
    //return length;
}

int status_return() {
    return status;
}

