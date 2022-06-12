//使用管道实现兄弟进程间通信，使兄弟进程实现命令ls | wc -l 的功能
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main(){

    int fd[2];
    int ret = pipe(fd);
    if(ret == -1){
        perror("pipe err");
        exit(1);
    }

    int i;
    pid_t pid,wpid;
    for(i = 0;i<2;i++){
        if((pid = fork()) == 0)
            break;
    }
    if( 2 == i){
        //父进程
        close(fd[0]);
        close(fd[1]);
        wpid = wait(NULL);
        printf("wait child 1 success,pid = %d \n",wpid);
        pid = wait(NULL);
        printf("wait child 2 success,pid = %d \n",pid);
    }else if(i == 0){
        //子进程写

        close(fd[0]);
         //将fd [1]所指文件内容定向到标准输出
        dup2(fd[1],STDOUT_FILENO);
        execlp("ls","ls",NULL);
    }else if(i == 1){
        //子进程读

        close(fd[1]);
         //将fd [1]所指文件内容定向到标准输出
        dup2(fd[0],STDIN_FILENO);
        execlp("wc","wc","-l",NULL);
    }

    return 0;
}