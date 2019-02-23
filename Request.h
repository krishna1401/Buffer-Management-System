#ifndef REQUEST_H
#define REQUEST_H

#include <bits/stdc++.h>
#include <iostream>
#include <string>
using namespace std;
struct Request{
    int processID;
    int blockNumber;
    int requestType;
    /*
        Request Type
    1 - Get Block Buffer
    2 - Release Allocated Block Buffer
    3 - Release Allocated Block Buffer with Delayed Write
    */
    
    int string_to_integer(string stringNumber){
        int number = 0;
        string digits = "0123456789";
        int length = stringNumber.size();
        
        for(int iterator = 0;iterator < length;iterator++){
            number = (number*10) + digits.find(stringNumber.at(iterator));
        }
        return number;
    }
    
public:
    Request(){
        processID = 0;
        blockNumber = 0;
        requestType = 0;
    }
    
    Request(int processID,int blockNumber,int requestType){
        this->processID = processID;
        this->blockNumber = blockNumber;
        this->requestType = requestType;
    }
    
    Request(string data){
    //Tokenizing the String into data
        stringstream tokenizer(data);
        string temporary;
        
        getline(tokenizer,temporary,' ');
        processID = string_to_integer(temporary);
        
        getline(tokenizer,temporary,' ');
        blockNumber = string_to_integer(temporary);
        
        getline(tokenizer,temporary,' ');
        requestType = string_to_integer(temporary);
    }
    
    void display(){
        cout<<"*****Request Information*****"<<endl;
        
        cout<<"Process ID : ";
        if(processID != 0){
            cout<<processID<<endl;
        }else{
            cout<<"No Request\n";
        }
        
        cout<<"Block Number : "<<blockNumber<<endl;
        if(blockNumber != 0){
            cout<<blockNumber<<endl;
        }else{
            cout<<"No Request\n";
        }
        
        cout<<"Request Type : ";
        if(requestType == 1){
            cout<<"Get Buffer Request\n";
        }else if(requestType == 2){
            cout<<"Release Buffer Request\n";
        }else if(requestType == 3){
            cout<<"Release Buffer Request with Delayed Write\n";
        }
    }
};

#endif
