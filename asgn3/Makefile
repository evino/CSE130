CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -pthread


all: queue.o

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

queue_test: queue_test.o queue.o
	$(CC) $(CFLAGS) -o queue_test queue_test.o queue.o

test: test.o queue.o
	$(CC) $(CFLAGS) -o test test.o queue.o


%.o: %.c
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f queue.o queue test.o test


format:
	clang-format -i -style=file queue.c queue.h test.c
