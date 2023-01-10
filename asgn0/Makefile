CC = clang
CFLAGS = -Wall -Wpedantic
LDFLAGS = -lm

all: hello

hello: hello.o
	$(CC) $(LDFLAGS) -o hello hello.o

clean:
	rm -f hello hello.o

format:
	clang-format -i -style=file hello.c