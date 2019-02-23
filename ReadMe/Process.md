> It replicates the working to a **process** within the operating system

## Global Variables
1. **pid**: Specifies the Process ID Number 
2. **remainingRequests**: Counts the number of requests remaining to be processed
3. **currentBlockNumber**: Stores the Number of the Block whose request is currently being processed

## Functions
1. **requestedBlock(...)**: It responds to a *user signal* defining the successfull completion of *getBlk* request made by the process and also adding new request to the queue for *release for the buffer*
2. **releasedBlock(...)**: It responds to the *user signal* defining the successfull completion of *brelse* algorithm.
3. **main()***: It performs the following task:
            - Randomly selects the maximum number of request to be made by a process
            - Define the signals that a process will catch
            - Make a request for a random block in a sequential order i.e. request for next buffer is only made after the first buffer is released
            - Add request to the secondary_queue for processing and wait for the request to complete
