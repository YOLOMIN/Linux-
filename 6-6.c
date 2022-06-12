//使用父進程等待進程組中某個指定的進程，若該進程不退出，則讓父進程一直堵塞
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(){

    pid_t pid,w,p;
    pid = fork();
    if(pid == -1){
        perror("fork1 error");
        exit(1);

    }else if(pid == 0){  //子進程
        sleep(5);
        printf("First child process:pid =%d\n",getpid());
        
    }else if(pid > 0){  //父進程繼續創建子進程
        int i;
        p = pid;
        for(i = 0;i < 3;i++){
            if((pid = fork()) == 0)  //如果是父進程則退出
                break;
        }

        if(pid == -1){
            perror("fork error");
            exit(2);
        }else if(pid == 0){
            printf("Child process:pid = %d \n",getpid());
            exit(0);
        }else if(pid > 0){   //父進程
            w = waitpid(p,NULL,0);  //等待第一個子進程執行
            if (w == p){
                printf("Catch a child Process:pid = %d \n",w);
            }else{
                printf("waitpid error\n");
            }

        }



    }


    return 0;
}