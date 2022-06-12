#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
//在原线程和新线程中分别进行打印操作，使原线程分别打印HELLO WORLD，新线程分别打印hello world。
pthread_mutex_t m;        //定义互斥锁

void err_thread(int ret,char *str){
	
	if(ret != 0 ){
		fprintf(stderr,"%s:%s\n",str,strerror(ret));
		pthread_exit(NULL);
	}

}

void *tfn(void *arg)
{
	srand(time(NULL));
	while(1){
		pthread_mutex_lock(&m);
		printf("hello ");
		//模拟长时间操作共同资源，导致CPU易主
		sleep(rand()%3);
		printf("world\n");
		pthread_mutex_unlock(&m);
		sleep(rand()%3);
	}
	return NULL;
}

int main(void){

	pthread_t tid;
	srand(time(NULL));
	int flag = 5;
	//初始化mutex:m=1
	pthread_mutex_init(&m,NULL);
	int ret = pthread_create(&tid,NULL,tfn,NULL);
	err_thread(ret,"pthread_create error");

	while(flag--){
		pthread_mutex_lock(&m);		//加锁：m--
		printf("HELLO ");
		sleep(rand()%3);
		printf("WORLD\n");
		pthread_mutex_unlock(&m);	//解锁：m++
		sleep(rand()%3);
	}
	pthread_cancel(tid);
	pthread_join(tid,NULL);
	pthread_mutex_destroy(&m);
	return 0;
}

