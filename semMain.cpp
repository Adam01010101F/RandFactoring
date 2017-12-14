/**
 * Adam Flores 
 * CECS 326 MW AM Class
 * Seamphore - Main
 **/
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <vector>
#include "semaphore.h"

using namespace std;

int getLoc(vector<long>, long);
enum {uSem, vSem};


int main(){
     srand(time(NULL));
     int two  = 2;
     int qid = 0;
     SEMAPHORE sem(two);//= new SEMAPHORE(two);
     sem.V(uSem);
     sem.V(vSem);
     int num =-1;
     long parentPID = getpid();
     vector<long> childPID;
     string qString;
     do{
          childPID.push_back(fork());
          num++; 
     }while(getpid()==parentPID && childPID.size()<4);
     
     if(getpid()==parentPID){
          createConnection();         
     }
     else{
          cout<<num<<": ";
          if(num %2 ==0){          
               int U = 827395609;
               sem.P(uSem);
               while(1){
                    int R = rand();
                    if(R<100 || R%U==0){
                         break;}
                    else{
                         cout<<num<<": "<<U<<"/"<<R<<" = "<<U/R
                                  <<endl;}
               }
               sem.V(uSem);
               
          }
          else{
               int V = 962094883;
               sem.P(vSem);
               while(1){
                    int R = rand();
                    if(R<100 || R%V==0){
                         break;}
                    else{
                         cout<<num<<": "<<V<<"/"<<R<<" = "<<V/R
                                  <<endl;
                    }
               }
               sem.V(vSem);
          }
     }
          
     
    return 0;  
}

int getInt(){
     return rand();
}


//Might not be needed
int getLoc(vector<long> cPID, long target){
    for(int i=0; i<(int)cPID.size();i++){
          if(cPID.at(target)==0){return i;};
     }
     return -1;
}


/**
 * Alerts Sender 251/997 that the msgQ is established
 **/
 int estConnection(){
    //Creating msgQ
    std::cout<<"Establishing Connection...\n";
    int qid = msgget(ftok(".",'u'), 0);
    buf msg;
    int size = sizeof(msg) - sizeof(long);
    
    //Sending est. msgs
    msg.mtype = 251;
    msg.content = 711;
    msgsnd(qid, (struct buf*)&msg, size, 0);
    msg.mtype=997;
    msgsnd(qid, (struct buf*)&msg, size, 0);
    
    //Receiving est. msgs
    msgrcv(qid, (struct buf*)&msg, size, 512,0);
    std::cout<<"Transmitter 251 Found...\n";
    msgrcv(qid, (struct buf*)&msg, size, 513,0);
    std::cout<<"Transmitter 997 Found...\n"; 

    return qid;
 }
 
 /**
 * Alerts Sender 257/997 that the msgQ is established
 **/
 int createConnection(){
    std::cout<<"Establishing Connection...";
    int qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);
    buf msg;
    int size = sizeof(msg) - sizeof(long);
    
    //Sending est. msgs
    msg.mtype = 257;
    msg.content = 711;
    msgsnd(qid, (struct buf*)&msg, size, 0);
    msg.mtype=997;
    msgsnd(qid, (struct buf*)&msg, size, 0);
    
    //Receiving est. msgs
    msgrcv(qid, (struct buf*)&msg, size, 1024,0);
    std::cout<<"Transmitter 257 Found..\n";
    msgrcv(qid, (struct buf*)&msg, size, 1025,0); 
    std::cout<<"Transmitter 997 Found..\n";

    return qid;
 }
