# Phase 1: Initial Design
My current plan is to have `main()` function act as my dispatcher.
It will loop, and `PUSH()` each connection file descriptor (`connfd`)
onto a bounded-buffer (queue).There will be a function for the worker
threads (might need to create thread in this function) that calls `POP()`
on the queue, which will return the `connfd`. `handle_connection()` will
then be called on `connfd`. Phase 1 will not support synchronization, but
getting a basic multithreaded server is the goal.

# Phase 2: Synchronization
Implementing synchronization will allow multiple threads to run concurrently
on the same URI (file path), which was not possible before. This will ensure
atomicity by placing Reader-Writer locks on files, and ensuring only one file
can be created at a time.

## Implementation:
Using a bounded-buffer (queue), requests are recieved from a client
to the server through a socket. The dispatcher treats the client
connection as a file descriptor, which is pushed onto the bounded-buffer.
Individual worker threads then pop the client connections off the bounded-
buffer and perform either a `GET` or `PUT` request.

`GET` requests place a shared lock on the given file, ensuring
other `GET` requests to the same URI can be run concurrently. The
lock is needed to prevent any `PUT` request from writing to the
given file, while it's being read by some thread.

`PUT` requests use a mutex to lock file opening and creation
to ensure no two threads run `PUT` requests on the same file
concurrently, possibly resulting in file overwrites. Once
file is opened and/or created, an exclusive lock is placed
on the file and the mutex is released. The exclusive lock is
neccessary to prevent multiple threads writing to one file
concurrently. This will ensure that the writes be atomic.

# Usage:
1. Clone repo locally: `git clone https://git.ucsc.edu/cse130/cse130-winter23/section02/edodisho.git`
2. Using GNU's Make, compile program by entering `make` (Makefile
and all other source code must be present in current directory).
3. Start server by running `./httpserver <port number>`
4. Client can now send request to server using http request
formatting. `PUT` and `GET` requests are only supported at this
time.
