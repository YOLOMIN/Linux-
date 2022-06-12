#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(){

    pid_t pid;
    pid = fork();
    if(pid == -1){
        perror("fork error");
        exit(1);
    }else if(pid > 0){
        printf("parent process:pid=%d \n",getpid());
    }else if(pid == 0){
        printf("child process:pid = %d\n",getpid());
        execl("/bin/ls","-a","-l","6-3.c",NULL);
        execlp("ls","-a","-l","6-3.c",NULL);
        char * arg[] ={"-a","-l","6-3.c",NULL};
        execvp("ls",arg);
        printf("child process:pid=%d\n",getpid());
    }


    return 0;
}