#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "parse.h"
#include "asgn2_helper_funcs.h"

void bad_req(Command *com);

void not_imp(Command *com);

void not_sup(Command *com);

void not_found(Command *com);

void forbid(Command *com);

void get_response(Command *com, int fd);

void put_response(Command *com, int fd);
