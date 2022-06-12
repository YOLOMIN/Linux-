#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
/*
使用FIFO实现没有亲缘关系进程间的通信，由于是没有亲缘关系的进程间通信
因此，需要在两段程序中实现，在程序fifo_write.c中实现FIFO的写操作
在程序fifo_read.c中实现FIFO的读操作
*/
int main(int argc,char *argv[]){
	
	//判断是否传入文件名
	if(argc < 2){
		printf("./a.out fifoname\n");
		exit(1);
	}
	//判断fifo文件是否存在
	int ret = access(argv[1],F_OK);
	//若fifo不存在就创建fifo
	if(ret == -1){
		int r = mkfifo(argv[1],644);
		//判断文件是否创建成功
		if(r == -1){
			perror("mkfifo");
			exit(1);
		}else{
			printf("fifo creat succes!\n");
		}
	}
	
	//以读写的方式打开文件
	int fd = open(argv[1],O_RDONLY);
	if(fd == -1){
		perror("open");
		exit(1);
	}
	//不断读取fifo中的数据并打印
	while(1){
		char buf[1024] ={0};
		read(fd,buf,sizeof(buf));
		printf("buf = %s \n",buf);
	}
	close(fd);


	return 0;
}
