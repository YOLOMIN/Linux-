#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
//使用wait函數同步進程，並使用宏函數獲取子進程的返回值

int main(){

    int status;
    pid_t pid,w;

    pid = fork();

    if(pid == -1){
        perror("fork error");
        exit(1);
    }else if(pid == 0){
        sleep(3);
        printf("Child process:pid=%d\n",getpid());
        exit(5);
    }else if(pid > 0){

        w = wait(&status);
        //用於判斷子程序是否正常退出，若是則返回非靈值，否則則返回0
        if(WIFEXITED(status)){
            printf("Child process pid = %d exit normally.\n",w);
            printf("Return Code : %d\n",WEXITSTATUS(status));
        }else{
            printf("Child process pid = %d exit abnormally.\n",w);
        }
    }


    return 0;
}