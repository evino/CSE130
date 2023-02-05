
#include <regex.h>
#include <assert.h>
#include <stdbool.h>


#include "parse.h"
#include "helpers.h"

// FOR DB
#include <stdio.h>

#define REQUEST_REGEX "^([a-zA-Z]{1,8}) (/[a-zA-Z0-9._]{1,63}) (HTTP/[0-9].[0-9])\r\n"

void request_parse(Command *com) {
    regex_t re;
    regmatch_t matches[4];
    int rc;

    rc = regcomp(&re, REQUEST_REGEX, REG_EXTENDED);
    assert(!rc); // MAY NEED INTERNAL SERVER ERROR HERE

    bool badRequest = false;

    rc = regexec(&re, (char *) com->buf, 4, matches, 0);
    if (rc == 0) {
        com->request_line = com->buf;

        com->method = com->buf + matches[1].rm_so;
        com->method[matches[1].rm_eo - matches[1].rm_so] = '\0';

        com->URI = com->buf + matches[2].rm_so;
        com->URI[matches[2].rm_eo - matches[2].rm_so] = '\0';

        com->version = com->buf + matches[3].rm_so;
        com->version[matches[3].rm_eo - matches[3].rm_so] = '\0';
        //   com->method = &REQUEST_REGEX[matches[1].rm_so];// - matches[1].rm_so;
        //com->method[matches[1].rm_eo] = '\0';  // NEED TO FIGURE OUT WHY method is NULL
    } else {
        printf("NOOOOOOO MATCHOOOOO\n");
        badRequest = true;
    }

    if (badRequest == true) {
        printf("SHOULD PRINT A BAD REQUEST here\n");
    }


    //printf("db: %s\n", matches[0]);
    // DEBUG PRINTS
    printf("method: %s\n", com->method);
    printf("URI: %s\n", com->URI);
    printf("version: %s\n", com->version);
}
// CALL REGFREE
