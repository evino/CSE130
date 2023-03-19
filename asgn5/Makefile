CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

list: list.o
	$(CC) $(CFLAGS) -o list.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<