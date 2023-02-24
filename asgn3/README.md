# Assignment 3 directory

This directory contains source code and other files for Assignment 3.

## Files:
    1. queue.h
        - Queue function prototypes.
    2. queue.c
        - Contains implementation of queue functions. Supports
        multithreading.
    3. Makefile
        - Makefile used to simplify compilation process.
    4. README.md
        - Documentation of files included in directory.

## Design:
The design for this assignment was fairly straightforward. The queue
was implemented using a dynamically allocated array that holds void
pointers. An array was used rather than a linked-list, since its more
memory efficient.

I used locks for my threading primitive, since I find them more
intuitive than semaphores. I also had to use condition variables in
conjunction with the locks. This is to prevent busy-waits when
blocking on a `PUSH()` to a full queue, or a `POP()` from an empty
queue.

Three mutexes are being used. One for `PUSH()`, one for `POP()`,
and one to keep my count increment/decrement atomic.

Two conditional variables are also being used. One for `PUSH()`
and one for `POP()`.

### Compilation:
Using the Makefile, the user will compile the `queue.c` file into
an object file, named `queue.o`, by entering `make` into the
command line. This object file must be linked with another program
supplied by the user.
