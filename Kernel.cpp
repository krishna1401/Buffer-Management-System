#include "Buffer.h"
#include "BufferCacheList.h"
#include "Request.h"
#include <fstream>  //File Operations  
#include <unistd.h> //Unix Commands
#include <sys/wait.h>   //Wait Command
#include <string>   //String Library
#include <iostream>
using namespace std;


#define QUEUENUMBER 4
#define BUFFERNUMBER 8
#define REQUESTQUEUE 5

BufferCacheList **hashQueueArray;
BufferCacheList *freeList;
Request **requestQueue;

int hashValue(int blockNumber){
    int hashValue = 0;
    hashValue = blockNumber % QUEUENUMBER;
    return hashValue;
}

//Display
void display(){
    cout<<"Hash Queue Details \n";
    for(int i = 0;i < QUEUENUMBER;i++){
        hashQueueArray[i]->displayHashQueue();
    }
    cout<<"Free List Details \n";
    freeList->displayFreeList();
}


//Get Buffer
Buffer* getblk(int blockNumber){
    Buffer* allocatedBuffer = NULL;
    int hashQueueNumber = hashValue(blockNumber);
    Buffer* blockBuffer = hashQueueArray[hashQueueNumber]->findBuffer(blockNumber,'H');
    if(blockBuffer != NULL){ //Buffer Buffer on Hash Queue
        if(blockBuffer->status == 0 || blockBuffer->status == 3){ //Case 1: Buffer on Hash Queue & Free
            allocatedBuffer = blockBuffer;
            freeList->removeSpecificBuffer(blockNumber,'F');  //Remove Buffer Buffer from Free List
        }else if(blockBuffer->status == 1){ //Case 5: Buffer on Hash Queue & Busy
            cout<<"Buffer Busy. Process should Sleep.\n";
        }else if(blockBuffer->status == 2){ 
            cout<<"Cleaning Buffer. \n";
            allocatedBuffer = blockBuffer;
        }
    }else{ //Buffer Buffer not on Hash Queue
        Buffer* freeBuffer = freeList->removeBufferFromHeadFreeList();
        if(freeBuffer != NULL){
            if(freeBuffer->status == 3){   //Case 3: Buffer on Free List Marked Delayed Write
                //Setting forked Process to show Delayed Write Condition
                cout<<"Delayed Write\n";
                int ret_code;
                if(fork() == 0){
                    sleep(2);   //Delayed Write for 5 seconds
                }
                int ret_val = wait(&ret_code);
                freeBuffer->status = 0;
                freeList->insertBufferAtHeadFreeList(freeBuffer); //Adding Buffer to Start of Free List After Delayed Write
            }else{  //Case 2: Buffer allocated from Free List
                allocatedBuffer = freeBuffer;
                hashQueueArray[hashQueueNumber]->insertBufferAtTail(freeBuffer,'H');
            } 
        }else{  //Case 4: No Buffer Available
            cout<<"No Free Buffer Available. Process Sleeps\n";
        }
    }
    return allocatedBuffer;
}

// Buffer Release
bool brelse(int blockNumber,int status){
    bool blockFreed = false;
    int hashQueueNumber = hashValue(blockNumber);
    Buffer* block = hashQueueArray[hashQueueNumber]->findBuffer(blockNumber,'H');
    if(block != NULL){
        blockFreed = true;
        block->status = status;
        freeList->insertBufferAtTail(block,'F');
    }
    return blockFreed;
}

//Update Data in Buffer Buffer
void updateBuffer(Buffer* buffer,int blockNumber,int processID,string data){
    buffer->blockNumber = blockNumber;
    buffer->processID = processID;
    buffer->data = data;
    buffer->status = 1;
}

//Read Request from Secondary Queue
int updateRequestQueue(){
    fstream fin,fout;
    fin.open("secondary_queue.ssv",ios::in);
    fout.open("secondary_queue_temporary.ssv",ios::out);
    
    string line;
    int iterator = 0;
    while(getline(fin,line)){
        if(iterator < REQUESTQUEUE){
            requestQueue[iterator] = new Request(line);
            iterator++;
        }else{
            fout<<line<<"\n";
        }
    }
    
    //Closing both the Files
    fin.close();
    fout.close();
    
    //Replacing old File with New File
    remove("secondary_queue.ssv");
    rename("secondary_queue_temporary.ssv","secondary_queue.ssv");
    
    return iterator;
}

//Adding Failed Buffer Request at End of Queue
void addFailureRequest(Request* failure){
    fstream fout;
    fout.open("secondary_queue.ssv",ios::app);
    fout<<failure->processID<<" "<<failure->blockNumber<<" "<<failure->requestType<<"\n";
    fout.close();
}

int main(){
    
    //Creating & Initializing an Array of Hash Queue Lists;
    hashQueueArray = new BufferCacheList*[QUEUENUMBER];
    for(int iterator = 0;iterator < QUEUENUMBER;iterator++)
    {
        hashQueueArray[iterator] = new BufferCacheList();
    }
    
    //Creating & Initializing Free List
    freeList = new BufferCacheList();
    for(int iterator = 0;iterator < BUFFERNUMBER;iterator++){
        freeList->insertBufferAtHeadFreeList(new Buffer());
    }
    
    //Creating & Initializing Request Queue
    requestQueue = new Request*[REQUESTQUEUE];
    for(int iterator = 0;iterator < REQUESTQUEUE;iterator++){
        requestQueue[iterator] = new Request();
    }
    
    int requestBlockNumber;
    int no_of_requests;
    while(true){
        no_of_requests = updateRequestQueue();
        if(no_of_requests > 0){
            for(int iterator = 0;iterator < no_of_requests;iterator++){
                requestBlockNumber = requestQueue[iterator]->blockNumber;
                if(requestBlockNumber != 0){   //Valid Block Request
                    if(requestQueue[iterator]->requestType == 1){   //Get Block Request
                        Buffer* block = getblk(requestBlockNumber);
                        if(block != NULL){
                            updateBuffer(block,requestBlockNumber, requestQueue[iterator]->processID, "Allocated");
                            display();
                            kill(requestQueue[iterator]->processID,30);
                        }else{
                            addFailureRequest(requestQueue[iterator]);
                        }
                    }else if(requestQueue[iterator]->requestType == 2){ //Release Block Buffer
                        brelse(requestBlockNumber,0);
                        display();
                        kill(requestQueue[iterator]->processID,31);
                    }else if(requestQueue[iterator]->requestType == 3){ //Release Block Buffer with Delayed Write
                        brelse(requestBlockNumber,3);
                        display();
                        kill(requestQueue[iterator]->processID,31);
                    }
                    requestQueue[iterator] = new Request(); //Resetting the Queue Slot
                }
            }
        }
        sleep(1);
    }
    
    /*
    //Menu Driver Program
    int choice = 0;
    bool loopCondition = true;
    do{
        cout<<"\n***********************\n";
        cout<<"1. Get New Buffer \n";
        cout<<"2. Release Buffer \n";
        cout<<"3. Print Data Structure \n";
        cout<<"4. Exit \n";
        cout<<"Select One Choice : ";
        cin>>choice;       
        
        switch(choice){
            case 1:{
            
                        int blockNumber;
                        cout<<"Enter Buffer Number : ";
                        cin>>blockNumber;
                        int processID;
                        cout<<"Enter Process Id : ";
                        cin>>processID;
                        string data;
                        cout<<"Enter data not more than 1024 bytes : ";
                        cin>>data;
                        Buffer* block = getblk(blockNumber);
                        if(block != NULL){
                            updateBuffer(block,blockNumber,processID,data);
                            cout<<"Buffer successfully Allocated\n";
                        }else{
                            cout<<"Free Buffer Not Allocated \n";
                        }
                        break;
                    }
            case 2:{
                        int blockNumber;
                        cout<<"Enter Buffer Number : ";
                        cin>>blockNumber;
                        if(brelse(blockNumber,0)){
                            cout<<"Buffer Successfully Removed\n";
                        }else{
                            cout<<"No such block in Hash Queues\n";
                        }
                        break;
                    }
            case 3: display();
                    break;
            case 4:
                    cout<<"Terminating";
                    loopCondition = false;
                    break;
            default: cout<<"Please Select a Valid Choice !!!\n";
        }
    }while(loopCondition);
    */
    return 0;
}
