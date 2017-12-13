/**
 * Adam Flores 
 * CECS 326 MW AM Class
 * Seamphore - Main
 **/
#include <iostream>
#include <vector>			
#include <cstdlib>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "semaphore.h"

int getLoc(std::vector<long>, long);

enum {uSem, vSem};


int main(){
     srand(time(NULL));
     SEMAPHORE sem(2);
     uSem.V(uSem);
     vSem.V(vSem);
     int num =-1;
     long parentPID = getpid();
     std::vector<long> childPID;
     std::string qString;
     do{
          childPID.push_back(fork());
          num++; 
     }while(getpid()==parentPID && childPID.size()<4);
     
     if(getpid()==parentPID){
          std::cout<<"I am the parent"<<std::endl;          
     }
     else{
          std::cout<<num<<": ";
          if(num %2 ==0){          
               int U = 827395609;
               while(1){
                    int R = rand();
                    if(R<100 || R%U==0){
                         break;}
                    else{
                         std::cout<<num<<" - Remainder:"<<U%R<<std::endl;
                    }
               }
          }
          else{
               int V = 962094883;
               while(1){
                    int R = rand();
                    if(R<100 || R%V==0){
                         break;}
                    else{
                         std::cout<<num<<" - Remainder:"<<V%R<<std::endl;
                    }
               }
          }
     }
          
     
          
}

int getInt(){
     return rand();
}


//Might not be needed
int getLoc(std::vector<long> cPID, long target){
    for(int i=0; i<(int)cPID.size();i++){
          if(cPID.at(target)==0){return i;};
     }
     return -1;
}

