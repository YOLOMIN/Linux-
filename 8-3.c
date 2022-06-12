#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
//使用popen函数和pclose函数实现管道通信
int main(){

    FILE *r_fp,*w_fp;
    char buf[100];
    //读取命令行执行结果
    r_fp = popen("ls","r");
    //将管道中的数据传递给进程
    w_fp = popen("wc -l","w");

    while(fgets(buf,sizeof(buf),r_fp)!=NULL)
        fputs(buf,w_fp);
    pclose(r_fp);
    pclose(w_fp);

    return 0;
}