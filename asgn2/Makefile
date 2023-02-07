CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
MEMCHECK = valgrind --leak-check=full
HTTP_OBJS = httpserver.o helpers.o parse.o request.o response.o
ECHO_OBJS = echo.o
HEADERS = asgn2_helper_funcs.h helpers.h parse.h request.h response.h

all: httpserver

#httpserver: httpserver.o helpers.o asgn2_helper_funcs.a
#	$(CC) $(CFLAGS) -o httpserver httpserver.o helpers.o asgn2_helper_funcs.a
httpserver: $(HTTP_OBJS) asgn2_helper_funcs.a
	$(CC) $(CFLAGS) -o httpserver $(HTTP_OBJS) asgn2_helper_funcs.a

%.o: %.c
	$(CC) $(CFLAGS) -c $<


echo: $(ECHO_OBJS) asgn2_helper_funcs.a
	$(CC) $(LDFLAGS) -o echo $(ECHO_OBJS) asgn2_helper_funcs.a

#echo.o: echo.c asgn2_helper_funcs.h
#	$(CC) $(CFLAGS) -c echo.c

clean:
	rm -f httpserver $(HTTP_OBJS) echo echo.o

format:
	clang-format -i -style=file httpserver.c echo.c helpers.c helpers.h parse.c parse.h request.c request.h response.c response.h
