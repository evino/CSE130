CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

hello: hello.o
	$(CC) -o hello hello.o

clean:
	rm -f hello hello.o

format:
	clang-format -i -style=file hello.c