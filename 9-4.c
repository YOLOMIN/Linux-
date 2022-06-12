#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
////在程序中使用pthread_cancel()函数使原线程终止指定线程
void * tfn(void * arg)
{
	while(1){
		printf("child thread....\n");
		pthread_testcancel();			//设置取消点
	}
}
int main(void)
{
	pthread_t tid;
	void *tret = NULL;
	pthread_create(&tid,NULL,tfn,NULL);
	sleep(1);
	pthread_cancel(tid);
	pthread_join(tid,&tret);
	printf("child thread exit code = %ld\n",(long int)tret);
	return 0;

}

