
#include <regex.h>
#include <assert.h>

#include "parse.h"
#include "helpers.h"

// FOR DB
#include <stdio.h>

#define REQUEST_REGEX "^([a-zA-Z]{1,8}) (/[a-zA-Z0-9._]{2,63}) (HTTP/[0-9].[0-9])\r\n"

void request_parse(Command *com) {
    regex_t re;
    regmatch_t matches[5];
    int rc;

    rc = regcomp(&re, REQUEST_REGEX, REG_EXTENDED);
    assert(!rc); // MAY NEED INTERNAL SERVER ERROR HERE

    rc = regexec(&re, (char *) com->buf, 5, matches, 0);
    if (rc == 0) {
        com->method = com->buf;
        com->method[matches[1].rm_eo] = '\0';
    }
    printf("db: %s\n", com->buf);
    printf("method: %s\n", com->method);
}
