#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
int main(){

    //設置計時器--計時結束後，內核會發送14信號SIGALRM到當前進程，進程收到該信號後默認終止運行
    
    alarm(1);
    while(1){
        printf("process will finish\n");
    }

    return 0;
}