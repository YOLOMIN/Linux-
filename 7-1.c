#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
int main(){

    pid_t pid;
    pid = fork();
    if(pid == 0){       //子進程
        sleep(1);
        printf("child pid = %d,ppid = %d \n",getpid(),getppid());
        kill(getppid(),SIGKILL);        //發送信號SIGKILL給父進程
    }else if(pid > 0){
        while(1){
            printf("parent pid = %d , ppid = %d \n",getpid(),getppid());
        }
    }

    return 0;
}