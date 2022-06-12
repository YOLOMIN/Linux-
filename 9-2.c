#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
//创建新线程，在新线程中修改原线程中定义的全局区的变量，并在原线程中打印该数据
//gcc 9-2.c -o ./9-2 -lpthread
int var = 100;
void * tfn(void * arg)
{
	var = 200;
	printf("thread\n");
	return NULL;
}
int main(void)
{
	printf("At first var = %d\n",var);
	pthread_t tid;
	pthread_create(&tid,NULL,tfn,NULL);
	sleep(1);
	printf("after pthread_create,var=%d\n",var);
	return 0;
}
