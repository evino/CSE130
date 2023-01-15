CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LDFLAGS = -lm

all: memory

memory: memory.o
	$(CC) $(LDFLAGS) -o memory memory.o

clean:
	rm -f memory memory.o

format:
	clang-format -i -style=file memory.c