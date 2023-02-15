CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -pthread
#QUEUE_SOURCE = queue.c
QUEUE_OBJS = queue.o
HEADERS = queue.h


queue.o: queue.c
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f queue.o


format:
	clang-format -i -style=file queue.c