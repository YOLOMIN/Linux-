#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
//sleep函數自實現
void sig_alrm(int signo){
        //do something.... 
         
}

unsigned int mysleep(unsigned int seconds){
     struct sigaction newact,oldact;
     unsigned int unslept;
     newact.sa_handler = sig_alrm;
     sigemptyset(&newact.sa_mask);
     newact.sa_flags = 0;
     sigaction(SIGALRM,&newact,&oldact);
     alarm(seconds);
     pause();
     return alarm(0);
}
int main(){

    while(1){
        mysleep(2);
        printf("two seconds passed.\n");
    }
    return 0;
}