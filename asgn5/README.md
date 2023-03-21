# Design

I wasn't able to find enough time to finish this assignment, but
I made sure to get the foundation laid, so I can complete it in the
future if I want to.

For the FIFO and LRU caches, I planned on using a queue as the
underlying data structure for the cache, and using a singly-linked
list to hold the "history" of nodes pushed into the cache. I chose
a list over an array since it was easier to have a dynamically-sized
list, rather than having to resize an array whenever more space
was needed.

# Future improvements
The plan is to add in checks for various miss types, and
take user input to add into the cache from standard input.
