CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

list_test: list_test.o list.o
	$(CC) $(CFLAGS) -o list_test list_test.o list.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f list_test list_test.o list.o
	