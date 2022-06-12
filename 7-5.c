#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
//自定義信號處理
//爲2號信號SIGINT設置自定義信號處理函數，並在信號處理函數中將函數恢復爲默認值
void sig_int(int signo){
    printf("............catch you,SIGINT.....,....\n");
    signal(SIGINT,SIG_DFL);
}

int main(){

    //捕獲信號SIGINT，修改信號處理函數
    signal(SIGINT,sig_int);
    
    while(1);

    return 0;
}