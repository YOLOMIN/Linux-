#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define MAXLINE 80		//最大数据长度
#define SERV_PORT 6666		//服务器端口号

int main(int argc,char *argv[]){

	struct sockaddr_in servaddr;	//定义服务器地址结构体
	char buf[MAXLINE];
	int sockfd,n;
	char *str;
	
	if(argc !=2 ){
		fputs("usage:./client message\n",stderr);
		exit(1);
	}
	str = argv[1];

	//创建客户端套接文件
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	//初始化客户端口地址
	bzero(&servaddr,sizeof(servaddr));	
	
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);
	//请求链接
	connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	//发送数据
	send(sockfd,str,strlen(str),0);
	//接收服务器返回的数据
	n = recv(sockfd,buf,MAXLINE,0);
	
	printf("Response from server:\n");
	//将服务器返回的数据打印到终端
	write(STDOUT_FILENO,buf,n);
	//关闭链接
	close(sockfd);

	return 0;
}




