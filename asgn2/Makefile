CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LDFLAGS = -lm
MEMCHECK = valgrind --leak-check=full
BASE_SOURCES = httpserver.c
BASE_OBJECTS = httpserver.o
HEADERS = asgn2_helper_funcs.h

all: httpserver

#httpserver: httpserver.o asgn_2_helper_funcs.a
#	$(CC) $(CFLAGS) $(LDFLAGS) -o httpserver httpserver.o

httpserver: httpserver.o asgn2_helper_funcs.a
	$(CC) $(LDFLAGS) -o httpserver httpserver.o

httpserver.o: $(BASE_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -c $(BASE_SOURCES)


echo: echo.o asgn2_helper_funcs.a
	$(CC) $(LDFLAGS) -o echo echo.o

echo.o: echo.c asgn2_helper_funcs.h
	$(CC) $(CFLAGS) -c echo.c

clean:
	rm -f httpserver httpserver.o

format:
	clang-format -i -style=file httpserver.c