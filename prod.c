
    /*Thread synchronization using counting semaphores. Application to demonstrate: 
producer-consumer problem with counting semaphores and mutex.*/


#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
int buf[5],f=0,r=0;
sem_t full,empty;
pthread_mutex_t Lock;
void *produce()
{
    int i;
    for(i=0;i<10;i++)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&Lock);
        printf("produced item is %d\n",i);
        buf[(++r)%5]=i;
        sleep(1);
        pthread_mutex_unlock(&Lock);
        sem_post(&full);
    }
}
void *consume()
{
        int item,i;
        for(i=0;i<10;i++)
        {
                sem_wait(&full);
                pthread_mutex_lock(&Lock);
                item=buf[(++f)%5];
                printf("consumed item is %d\n",item);
                sleep(1);
                pthread_mutex_unlock(&Lock);
                sem_post(&empty);
        }
}
int main()
{
	int n;
        pthread_mutex_init(&Lock,NULL);
	pthread_t tid1[2];
	//sem_init(&mutex,0,1);
	sem_init(&empty,0,5);    
	sem_init(&full,0,0);
	
	pthread_create(&tid1[0],NULL,produce,NULL);
	pthread_create(&tid1[1],NULL,consume,NULL);
	pthread_join(tid1[0],NULL);
	pthread_join(tid1[1],NULL);
}
