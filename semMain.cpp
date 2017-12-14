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
int getInt();			
enum {uSem, vSem};


int main(){
    bool quit=false;
    srand(time(NULL));
    int two  = 2;
    int qid = 0;
    SEMAPHORE sem(two);
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
        cout<<getpid()<<" is the parent"<<endl;
        //createConnection();         
    }
    else{
        cout<<getpid();
        if(num %2 ==0){          
            int U = 827395609;
            sem.P(uSem);
            while(quit!=true){
                int R = getInt();
                if(R<100 || R%U==0){
                    cout<<"Ending\n";
                    quit=true;
                }else{
                    if(U%R==0){
                        cout<<num<<": "<<U<<"/"<<R<<" = "<<U/R
                            <<endl;}
                }
            }
            sem.V(uSem);
             
        }
        else{
            int V = 962094883;
            sem.P(vSem);
            while(quit!=true){
                int R = getInt();
                if(R<100 || R%V==0){
                    cout<<"Ending\n";
                    quit=true;
                }else{
                    if(V%R==0){
                    cout<<num<<": "<<V<<"/"<<R<<" = "<<V/R
                        <<endl;}
                }
           }
           sem.V(vSem);
       }
     }
          
    return 0;  
}

int getInt(){
    int min =0;
    int max = RAND_MAX;
    //return rand();
    return rand()%(max-min+1)+min;
}


//Might not be needed
int getLoc(vector<long> cPID, long target){
   for(int i=0; i<(int)cPID.size();i++){
       if(cPID.at(target)==0){return i;};
    }
    return -1;
}



