#pragma once

#include "helpers.h"

#define BUFF_SIZE 4096
typedef struct {
	char buf[BUFF_SIZE + 1];
    char *method;
	char *request;
	char *header;
} Command;


void request_parse(Command *com);
