# Introduction
> This project implements the Simple Buffer Management System used in Operating Systems at kernel level. It replicates the task
kernel in Buffer Management from allocation of buffers to freeing of buffers after use.

# How is Works
Each process adds a request for a particular buffer cache in the **secondary_queue.csv** file providing information about the
block number, process ID and request type. Kernel then fulfill one request at a time, and updating the buffer cache and free list
details accordingly.

# How to Run
1. Open Main terminal and execute the kernel.cpp file
2. Open multiple other terminals for various process (Number of Terminals = Number of Process)
3. Run process.cpp in all the other terminals.
4. Process randomly request a block and the Kernel terminal performs the task and update the Buffer Cache.
