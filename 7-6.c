#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
//sigaction--信號的捕獲
//使用sigaction函數修改2號信號SIGINT的默認動作
void sig_int(int signo){

    printf("........catch you,SIGNT,signo= %d \n",signo);
    sleep(5);  //  模擬信號處理函數執行時間

}


int main(){

    struct sigaction act,oldact;
    act.sa_handler = sig_int;           //修改信號處理函數指針
    sigemptyset(&act.sa_mask);          //初始化位圖，表示不屏蔽任何信號
    sigaddset(&act.sa_mask,SIGINT);     //更改信號SIGINT的信號處理函數
    act.sa_flags = 0;                   //設置flags，屏蔽自身所發送信號
    sigaction(SIGINT,&act,&oldact);
    while(1);


    return 0;
}