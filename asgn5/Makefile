CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

cacher: cacher.o fifo.o list.o queue.o
	$(CC) $(CFLAGS) -o cacher cacher.o list.o fifo.o queue.o

list_test: list_test.o list.o
	$(CC) $(CFLAGS) -o list_test list_test.o list.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f list_test list_test.o list.o cacher cacher.o fifo.o queue.o
	