CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LDFLAGS = -lm
MEMCHECK = valgrind --leak-check=full
BASE_SOURCES = httpserver.c
BASE_OBJECTS = httpserver.o
HEADERS = asgn2_helper_funcs.h helpers.h

all: httpserver


httpserver: httpserver.o helpers.o asgn2_helper_funcs.a
	$(CC) $(CFLAGS) -o httpserver httpserver.o helpers.o asgn2_helper_funcs.a
#	clang -o httpserver httpserver.o asgn2_helper_funcs.a

httpserver.o: $(BASE_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -c $(BASE_SOURCES)

#httpserver.o: httpserver.c asgn2_helper_funcs.h
#	$(CC) $(CFLAGS) -c httpserver.c


echo: echo.o asgn2_helper_funcs.a
	$(CC) $(LDFLAGS) -o echo echo.o asgn2_helper_funcs.a

echo.o: echo.c asgn2_helper_funcs.h
	$(CC) $(CFLAGS) -c echo.c

clean:
	rm -f httpserver httpserver.o echo echo.o helpers helpers.o

format:
	clang-format -i -style=file httpserver.c echo.c helpers.c helpers.h