# Phase 1: Initial Design
My current plan is to have `main()` function act as my dispatcher.
It will loop, and `PUSH()` each connection file descriptor (`connfd`)
onto a bounded-buffer (queue).There will be a function for the worker
threads (might need to create thread in this function) that calls `POP()`
on the queue, which will return the `connfd`. `handle_connection()` will
then be called on `connfd`. Phase 1 will not support syncronization, but
getting a basic multithreaded server is the goal.
