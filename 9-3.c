#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
//在一个进程中创建4个新线程，分别使用pthread_exit()函数，return，exit（）使其中一个线程退出
void * tfn(void * arg)
{
	long int i;
	i = (long int)arg;	//将void×类型的arg强转换为long int类型
	if(i == 2)
		pthread_exit(NULL);
	sleep(i);
	printf("I am %dth thread,Thread_ID = %lu\n",i+1,pthread_self());
	return NULL;
}
int main(int argc,char * argv[])
{
	long int n = 5,i;
	pthread_t tid;
	if(argc == 2)
		n=atoi(argv[1]);
	for(i = 0;i < n;i++){
		//将i转换为指针，在tfn中再强转回整形
		pthread_create(&tid,NULL,tfn,(void*)i);
	}
	sleep(n);
	printf("I am main,I 'm a thread!\n"
		"main_thread_ID = %lu\n",pthread_self());
	return 0;
}
