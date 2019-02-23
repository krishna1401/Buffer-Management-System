#ifndef Buffer_H
#define Buffer_H

#include <string>
#include <iostream>
using namespace std;
struct Buffer{
    int blockNumber;
    int processID;
    int status;
    string data;
    struct Buffer* nextHashQueue;
    struct Buffer* prevHashQueue;
    struct Buffer* nextFreeList;
    struct Buffer* prevFreeList;
public:
    Buffer(){
        blockNumber = 0;
        processID = 0;
        status = 0;
        data = "";
        nextHashQueue = prevHashQueue = 0;
        nextFreeList = prevFreeList = 0;
    }
    Buffer(int blockNumber, int processID, int status = 0, string data = " ", Buffer* nextHashQueue = 0, Buffer* prevHashQueue = 0, Buffer* nextFreeList = 0, Buffer* prevFreeList = 0){
        this->blockNumber = blockNumber;
        this->processID = processID;
        this->status = status;
        this->data = data;
        this->nextHashQueue = nextHashQueue;
        this->prevHashQueue = prevHashQueue;
        this->nextFreeList = nextFreeList;
        this->prevFreeList = prevFreeList;
    }
    
    void display(){
        cout<<"*****Buffer Information*****\n";
        
        cout<<"Block Number : ";
        if(blockNumber != 0){
            cout<<blockNumber<<endl;
        }else{
            cout<<"Buffer Not Allocated\n";
        }
        
        cout<<"Process ID : ";
        if(processID != 0){
            cout<<processID<<endl;
        }else{
            cout<<"Buffer Not Allocated\n";
        }
        
        cout<<"Status : ";
        if(status == 0){
            cout<<"Buffer Not Allocated\n";
        }else if(status == 1){
            cout<<"Buffer Currently Locked\n";
        }else if(status == 2){
            cout<<"Buffer Data Invalid\n";
        }else if(status == 3){
            cout<<"Buffer Marked Delayed Write\n";
        }else if(status == 4){
            cout<<"Process Waiting for Buffer\n";
        }
        
        cout<<"Data : "<<data<<endl; 
    }
};

#endif
