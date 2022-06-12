#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#define SEGSIZE 4096     //定义共享内存容量

typedef struct{
	char name[8];	//读写数据结构
	int  age;
}Stu;
int main(){
	int shm_id,i;
	key_t key;
	char name[8];
	Stu * smap;
	struct shmid_ds buf;
	key = ftok("/",0);		//获取关键字
	if(key == -1)
	{
		perror("ftok error");
		return -1;
	}
	printf("key=%d\n",key);
	//创建共享内存
	shm_id = shmget(key,0,0);
	if( shm_id == -1)
	{
		perror("create shared memory error\n");
		return -1;
	
	}
	printf("shm_id = %d\n",shm_id);
	smap = (Stu* ) shmat(shm_id,NULL,0);		//将进程与共享内存绑定
	for(i = 0;i < 3;i++)	//读数据
	{	
		printf("name:%s\n",(*(smap+i)).name);
		printf("age :%d\n",(*(smap+i)).age);
	}
	if(shmdt(smap) == -1)	//解除绑定
	{
		perror("detach error");
		return -1;
	}
	//删除共享内存
	shmctl(shm_id,IPC_RMID,&buf);		

	return 0;
}

