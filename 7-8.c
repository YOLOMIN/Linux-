#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
//使用alarm和sigsuspend自實現mysleep函數

void sig_alrm(int signo){
        //do something.... 
         
}

unsigned int mysleep(unsigned int seconds){
     struct sigaction newact,oldact;
     unsigned int unslept;
     sigset_t newmask,oldmask,suspmask;
     
     //爲SIGALRM設置捕獲函數
     newact.sa_handler = sig_alrm;
     sigemptyset(&newact.sa_mask);
     newact.sa_flags = 0;
     sigaction(SIGALRM,&newact,&oldact);    
    //設置阻塞信號集，屏蔽信號SIGALRM
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGALRM);
    sigprocmask(SIG_BLOCK,&newmask,&oldmask);
    //設置計時器
     alarm(seconds);                        //倒計時
     
     //構造臨時阻塞信號集
     suspmask = oldmask;
     sigdelset(&suspmask,SIGALRM);
     //採用臨時阻塞信號集suspmask替換原有阻塞信號集
     sigsuspend(&suspmask);
     unslept = alarm(0);
     //恢復SIGALRM原有的處理動作，呼應17行注釋
     sigaction(SIG_SETMASK,&oldmask,NULL);
     
     return alarm(0);                       //返回
}
int main(){

    while(1){
        mysleep(2);
        printf("two seconds passed.\n");
    }
    return 0;
}