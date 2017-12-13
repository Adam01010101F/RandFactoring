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

int getLoc(vector<long>, long);

enum {uSem, vSem};
using namespace std;

int main(){
     srand(time(NULL));
     SEMAPHORE sem(2);
     //sem.V(uSem);
     //sem.V(vSem);
     int num =-1;
     long parentPID = getpid();
     vector<long> childPID;
     string qString;
     do{
          childPID.push_back(fork());
          num++; 
     }while(getpid()==parentPID && childPID.size()<4);
     
     if(getpid()==parentPID){
          cout<<"I am the parent"<<endl;          
     }
     else{
          cout<<num<<": ";
          if(num %2 ==0){          
               int U = 827395609;
               while(1){
                    int R = rand();
                    if(R<100 || R%U==0){
                         break;}
                    else{
                         cout<<num<<": "<<U<<"/"<<R<<" = "<<U/R
                                  <<endl;}
               }
          }
          else{
               int V = 962094883;
               while(1){
                    int R = rand();
                    if(R<100 || R%V==0){
                         break;}
                    else{
                         cout<<num<<": "<<V<<"/"<<R<<" = "<<V/R
                                  <<endl;
                    }
               }
          }
     }
          
     
          
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
