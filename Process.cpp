// Process Running Codes

/*
Assinging User Signals to Specific Tasks
Signal Number 30 - Requested Block Signal Recieved
Signal Number 31 - Released Block Signal Recieved
*/

#include <stdlib.h> //Random Generator
#include <time.h>   //Time Library
#include <unistd.h>   //Unix Commands
#include <fstream>  //File Operations
#include <csignal>  //Signal Commands
#include <iostream>
using namespace std;

#define MAXBLOCKNUMBER 50
int pid;
int remainingRequests = 0;
int currentBlockNumber;

void requestedBlock(int signum){
    sleep(2);
    fstream fout;
    fout.open("secondary_queue.ssv",ios::app);
    srand(time(NULL));
    int requestType = rand()%2 + 2; //Randomly select Delayed Write or Normal Read at release
    fout<<pid<<" "<<currentBlockNumber<<" "<<requestType<<"\n";
    cout<<"("<<currentBlockNumber<<" , "<<requestType<<")\n";   //Release Block Request
    fout.close();
}

void releasedBlock(int signum){
    remainingRequests -= 1;
}

int main(){
    pid = getpid();
    cout<<"Process ID : "<<pid<<"\n";
    srand(time(NULL)); //Initializing Random Seed
    
    int no_of_requests = rand()%10 + 1; //Maximum 10 request can be made by a process
    cout<<"No of Requests : "<<no_of_requests<<"\n";
    cout<<"(Block Number , Request Type)\n";
    
    signal(30,requestedBlock);
    signal(31,releasedBlock);

    int requestType = 1;    //Get Block Request
    for(int iterator = 1;iterator <= no_of_requests;iterator++){
        fstream fout;
        fout.open("secondary_queue.ssv",ios::app);
        srand(time(NULL));
        currentBlockNumber = rand()%MAXBLOCKNUMBER + 1;    //Block Number Range from 1 to 50
        srand(time(NULL));
        
        //Adding Request to the Secondary Queue
        remainingRequests += 1;
        fout<<pid<<" "<<currentBlockNumber<<" "<<requestType<<"\n";
        cout<<"("<<currentBlockNumber<<" , "<<requestType<<")\n";
        fout.close();   
        
        pause(); //Pause until the request is Completed
    }
    
    //Wait Until all the Requests are Completed
    while(remainingRequests != 0){
        pause();
    }
    
    return 0;
}
