CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -pthread
#QUEUE_SOURCE = queue.c
QUEUE_OBJS = queue.o
HEADERS = queue.h

queue.o: queue.c
	$(CC) $(CFLAGS) -c $<


test: queue.o test.o
	$(CC) $(CFLAGS) -o queue test.o


test.o: test.c queue.c
	$(CC) $(CFLAGS) -c $<





#queue.o: queue.c
#	$(CC) $(CFLAGS) -c $<


clean:
	rm -f queue.o test.o queue


format:
	clang-format -i -style=file queue.c