> It replicates the working of a **kernel** in the operating system

## Global Variables
1. **hashQueueArray**: Array to store pointers to all available Hash Queues
2. **freeList**: Pointer to the Free List
3. **requestQueue**: Array of Requests made to the kernel 

## Constants
1. **QUEUENUMBER**: Number of Hash Queues in the Kernel Cache
2. **BUFFERNUMBER**: Number of Buffers available in the Kernel Cache
3. **REQUESTQUEUE**: Number of Requests processed by Kernel in one iteration

## Functions
1. **hashValue(...)**: Returns the Hash Value for the specified Block Number
2. **display()**: Display the content of both Hash Queues and Free List
3. **getblk(...)**: Implements the basic *getblk* algorithm and returns the available buffer (if any)
4. **brelse(...)**: Implements the basic *brelse* algorithm
5. **updateBuffer(...)**: Updates the content of the buffer with specified values
6. **removeDuplicate(...)**: Removes any duplicates requests in the Request Queue
7. **updateRequestQueue()**: Writes the Request Queue with next set of available requests
8. **addFailureRequest(...)**: Re-writes any Failed Request into the secondary_queue for reprocessing
9. **main()**: This function performs the following tasks:
            - Initializes the Hash Queue Array, Free List and Request Queue 
            - Updates the Request Queue for new Requests
            - Process each request one at a time based on the Request Type
            - Signals the specified Process on successful completion the Request for the process
            - Displays the status of the Buffers in the Hash Queue and Free List after each Request is processed
            
