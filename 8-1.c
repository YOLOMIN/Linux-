#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
// 使用pipe實現父子進程間通，要求父進程作爲寫端，子進程作爲讀端
int main(){
    //定義文件描述符數組
    int fd[2];
    //創建管道
    int ret = pipe(fd);
    if(ret == -1){
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();

    if(pid > 0){
        //父進程---寫
        //关闭读端
        printf("I am farther!!!\n");
        close(fd[0]);
        char *p = "hello ,pipe\n";
        //写数据
        write(fd[1],p,strlen(p)+1);
        close(fd[1]);
        wait(NULL);
        printf("farther is exit!!!\n");
    }else if(pid == 0){
        //子进程-读
        //关闭写端
        printf("I am child!!!\n");
        close(fd[1]);
        char buf[64] ={0};

        //读数据
        ret = read(fd[0],buf,sizeof(buf));

        close(fd[0]);
        //将读到的数据写到标准输出
        write(STDOUT_FILENO,buf,ret);

        printf("child is exit!!!!\n");
    }

    return 0;
}