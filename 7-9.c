#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
//使用信號機制回收子進程
void sys_err(char * str){
    perror(str);
    exit(1);
}

//信號處理函數
void do_sig_child(int signo){
    waitpid(0,NULL,WNOHANG);
}
int main(void){
    pid_t pid;
    int i;
    for(i = 0;i<5;i++){
        //子進程
        if((pid = fork()) == 0){
            break;
        }else if(pid < 0){
            //容錯處理
            sys_err("fork");
        }
    }
    if(pid == 0){
        //子進程分支
        int n = 1;
        while(n--){
            printf("child ID %d\n",getpid());
        }
        exit(i+1);
    }else if(pid > 0){
        //父進程
        struct sigaction act;
        act.sa_handler = do_sig_child;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        sigaction(SIGCHLD,&act,NULL);
        while(1){
            printf("Parent ID %d\n",getpid());
            sleep(1);
        }
    }


    return 0;
}