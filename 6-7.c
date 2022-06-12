//使用waitpid 不斷獲取某進程的狀態

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(){

    pid_t pid,w;
    pid = fork();
    if(pid == -1){
        perror("fork1 error");
        exit(1);

    }else if(pid == 0){  //子進程
        sleep(3);
        printf("Child process:pid =%d\n",getpid());
        exit(0);
        
    }else if(pid > 0){  //父進程繼續創建子進程
        do{
            w = waitpid(pid,NULL,WNOHANG);
            if(w == 0){
                printf("No child exited\n");
                sleep(1);
            }
        }while(w == 0);

        if(w == pid)
            printf("Catch a child process:pid =%d \n",w);
        else
            printf("waitpid error\n");  

    }


    return 0;
}