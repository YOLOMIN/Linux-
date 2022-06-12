#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
int main(){

    pid_t pid;
    int i;
    for(i = 0;i < 5;i++){
        //循环创建进程
        //若当前进程为子进程，便跳出循环
       
        if((pid=fork()) == 0){
            break;
        }
    }
        if(pid == -1){
            perror("fork error");
            exit(1);
        }else if(pid > 0){
             //在調試的時候發現，一直讀是在創建父進程,why?
            printf("parent process:pid=%d\n",getpid());
        }else if(pid == 0){
            printf("I am child = %d ,pid = %d \n",i+1,getpid());
        }
    


    return 0;
}