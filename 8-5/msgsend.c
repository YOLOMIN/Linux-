#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<string.h>
#define MAX_TEXT 512

//消息结构体
struct my_msg_st{
	long int my_msg_type;		//消息类型
	char anytext[MAX_TEXT];		//消息数据

};
//使用消息队列实现不同进程间的通信
int main(){

	int idx = 1;
	int msqid;
	struct my_msg_st data;
	char buf[BUFSIZ];			//设置缓存变量
	msqid = msgget((key_t)1000,0644|IPC_CREAT);//创建消息队列
	if(msqid == -1){
		perror("msgget err");
		exit(-1);
	}
	
	while(idx < 5){					//发送消息
		printf("enter some text");
		fgets(buf,BUFSIZ,stdin);
		data.my_msg_type = rand()%3+1;		//随机获取消息类型
		strcpy(data.anytext,buf);
		//发送消息
		if(msgsnd(msqid,(void*)&data,sizeof(data),0) == -1){
			perror("msgsnd err");
			exit(-1);
		}
		idx++;

	}

	return 0;
}



