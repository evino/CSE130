#pragma once

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include "parse.h"
#include "asgn2_helper_funcs.h"

//char *status_phrase;

int file_check(Command *com);

void request_handler(Command *com);
