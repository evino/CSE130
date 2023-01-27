CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LDFLAGS = -lm
MEMCHECK = valgrind --leak-check=full

all: httpserver

httpserver: httpserver.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o httpserver httpserver.o


clean:
	rm -f httpserver httpserver.o

format:
	clang-format -i -style=file httpserver.c