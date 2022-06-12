#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
//  以2信號爲例，通過位操作函數sigprocmask以及sigpending獲取信號狀態

void printset(sigset_t * ped){
    int i;
    for(i = 1;i < 32;i++){
        if((sigismember(ped,i) == 1)){
            putchar('1');
        }else{
            putchar('0');
        }
    }
    printf("\n");
}

int main(){
    //信號集定義
    sigset_t set,oldset,ped;            
    //初始化自定義信號集set
    sigemptyset(&set);
    //將2信號SIGINT加入set
    sigaddset(&set,SIGINT);
    //位操作
    sigprocmask(SIG_BLOCK,&set,&oldset);
    while(1){
        sigpending(&ped);
        printset(&ped);
        sleep(1);
    }
    return 0;
}