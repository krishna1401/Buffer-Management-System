# Introduction
> This project implements the Simple Buffer Management System used in Operating Systems at kernel level. It replicates the task
kernel in Buffer Management from allocation of buffers to freeing of buffers after use.

# How is Works
1. Each process adds a request for a particular buffer cache in the **secondary_queue.csv** file providing information about the block number, process ID and request type.
2. Kernel reads request from the **secondary_queue.csv** and fulfill the request accordingly.
3. Kernel then sends signal to the requested process about the successfull completion of the request.
4. Process on recieving the signal, sends another request (if any).

# How to Run
1. Open Main terminal and execute the kernel.cpp file
2. Open multiple other terminals for various process (Number of Terminals = Number of Process)
3. Run process.cpp in all the other terminals.
4. Process randomly request a block and the Kernel terminal performs the task and update the Buffer Cache.
