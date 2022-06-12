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
//使用消息队列实现不同进程间的通信------接受端
int main(){

	int idx = 1;
	int msqid;
	struct my_msg_st data;
	long int msg_to_rcv = 0;
	
	//rcv msg
	msqid = msgget((key_t)1000,0644|IPC_CREAT);//创建消息队列
	if(msqid == -1){
		perror("msgget err");
		exit(-1);
	}
	
	while(idx < 5){					//接受消息
		
		//接收消息
		if(msgrcv(msqid,(void*)&data,BUFSIZ,msg_to_rcv,0) == -1){
			perror("msgrcv err");
			exit(-1);
		}
		//打印消息
		printf("msg type:%ld\n",data.my_msg_type);
		printf("msg content is:%s",data.anytext);
		idx++;

	}
	//删除消息队列
	if(msgctl(msqid,IPC_RMID,0) == -1){
		perror("msgctl err");
		exit(-1);
	}

	return 0;
}



