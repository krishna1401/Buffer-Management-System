#ifndef BUFFERCACHELIST_H
#define BUFFERCACHELIST_H

#include "Buffer.h"
#include <iostream>
using namespace std;

class BufferCacheList{
    Buffer* head;
    Buffer* tail;

public:
//Check if Linked List is Empty or Not
    bool isEmpty(){
        bool empty = false;
        if(head == NULL){
            empty = true;
        }
        return empty;    
    }

//Find a Buffer in the Linked List
    Buffer* findBuffer(int blockNumber,char listType){
        Buffer* foundBuffer = NULL;
        if(!isEmpty()){
            Buffer* temp = head;
            do{
                if(temp->blockNumber == blockNumber){
                    foundBuffer = temp;
                    break;
                }
                if(listType == 'H' || listType == 'h'){
                    temp = temp->nextHashQueue;
                }else if(listType == 'F' || listType == 'f'){
                    temp = temp->nextFreeList;
                }
            }while(temp != head);
        }
        return foundBuffer;
    }

//Search if a Buffer exsist in the Linked List
    bool searchBuffer(int blockNumber,char listType){
        bool searchedBuffer = true;
        if(findBuffer(blockNumber,listType) == NULL)
            searchedBuffer = false;
        return searchedBuffer;
    }
    
//Add Buffer at Start of the Free List
    void insertBufferAtHeadFreeList(Buffer* insertBuffer){
        if(head == NULL){
            insertBuffer->nextFreeList = insertBuffer->prevFreeList = insertBuffer;
            head = tail = insertBuffer;
        }else{
            insertBuffer->nextFreeList = head;
            insertBuffer->prevFreeList = tail;
            tail->nextFreeList = head->prevFreeList = insertBuffer;
            head = insertBuffer;
        }
    }

//Add Buffer at End of the Linked List
    void insertBufferAtTail(Buffer* insertBuffer,char listType){
        if(head == NULL){
            if(listType == 'H' || listType == 'h'){
                insertBuffer->nextHashQueue = insertBuffer->prevHashQueue = insertBuffer;
            }else if(listType == 'F' || listType == 'f'){
                insertBuffer->nextFreeList = insertBuffer->prevFreeList = insertBuffer;
            }
            head = tail = insertBuffer;
        }else{
            if(listType == 'H' || listType == 'h'){
                insertBuffer->prevHashQueue = tail;
                insertBuffer->nextHashQueue = head;
                head->prevHashQueue = tail->nextHashQueue = insertBuffer;
                tail = tail->nextHashQueue;
            }else if(listType == 'F' || listType == 'f'){
                insertBuffer->prevFreeList = tail;
                insertBuffer->nextFreeList = head;
                head->prevFreeList = tail->nextFreeList = insertBuffer;
                tail = tail->nextFreeList;
            }
        }
    }
    
//Remove Buffer from Head of the Free Linked List    
    Buffer* removeBufferFromHeadFreeList(){
        Buffer* removed = NULL;
        if(!isEmpty()){
            if(head == head->nextFreeList){ //Only Buffer in the Linked List
                removed = head;
                head = tail = NULL;
            }else{
                tail->nextFreeList = head->nextFreeList;
                head->nextFreeList->prevFreeList = head->prevFreeList;
                removed = head;
                head = head->nextFreeList;
            }
        }
        return removed;
    }

//Remove a Specific Buffer from Linked List
    bool removeSpecificBuffer(int blockNumber,char listType){
        bool removed = false;
        Buffer* temp = findBuffer(blockNumber,listType);
        
        if(listType == 'H' || listType == 'h'){
        //Hash Queue Removal
            if(temp->nextHashQueue == temp){ //Only Buffer in Linked List
                head = tail = NULL;
            }else{
                if(temp == head){ //If Head Buffer is the Buffer toBeRemoved from Linked List
                    head = head->nextHashQueue;
                }else if(temp == tail){ //If Tail Buffer is the Buffer toBeRemoved from Linked List
                    tail = tail->prevHashQueue;
                }
                temp->prevHashQueue->nextHashQueue = temp->nextHashQueue;
                temp->nextHashQueue->prevHashQueue = temp->prevHashQueue;
            }
        }else if(listType == 'F' || listType == 'f'){
        //Free List Removal
            if(temp->nextFreeList == temp){ //Only Buffer in Linked List
                head = tail = NULL;
            }else{
                if(temp == head){ //If Head Buffer is the Buffer toBeRemoved from Linked List
                    head = head->nextFreeList;
                }else if(temp == tail){ //If Tail Buffer is the Buffer toBeRemoved from Linked List
                    tail = tail->prevFreeList;
                }
                temp->prevFreeList->nextFreeList = temp->nextFreeList;
                temp->nextFreeList->prevFreeList = temp->prevFreeList;
            }
        }
        return removed;
    }

    void displayFreeList(){
        Buffer* temp = head;
        if(!isEmpty()){
            cout<<"Head :"<<head->blockNumber<<"\tTail :"<<tail->blockNumber<<"\n";
            do{
                cout<<"("<<temp->prevFreeList->blockNumber<<","<<temp->blockNumber<<","<<temp->nextFreeList->blockNumber<<","<<temp->status<<")\t";
                temp = temp->nextFreeList;
            }while(temp != head);
        }
        cout<<"\n**********************************************************\n";
    }
    
    void displayHashQueue(){
        Buffer* temp = head;
        if(!isEmpty()){
            cout<<"Head :"<<head->blockNumber<<"\tTail :"<<tail->blockNumber<<"\n";
            do{
                cout<<"("<<temp->prevHashQueue->blockNumber<<","<<temp->blockNumber<<","<<temp->nextHashQueue->blockNumber<<","<<temp->status<<")\t";
                temp = temp->nextHashQueue;
            }while(temp != head);
        }
        cout<<"\n**********************************************************\n";
    }
};
#endif
