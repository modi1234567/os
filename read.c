
/* Thread synchronization and mutual exclusion using mutex. Application to demonstrate:
Reader-Writer problem with reader priority.*/

#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
pthread_mutex_t x,wsem;
pthread_t tid,t1;
int readcount=0;
//int data=5;

void * reader (void * param)
{
    printf("\nReader is trying to enter");
    pthread_mutex_lock(&x);
    readcount++;
    if(readcount==1)
        pthread_mutex_lock(&wsem);
    printf("\n Reader is inside and data");
   pthread_mutex_unlock(&x);
    sleep(3);
    pthread_mutex_lock(&x);
    readcount--;
    if(readcount==0)
        pthread_mutex_unlock(&wsem);
    pthread_mutex_unlock(&x);
    printf("\nReader is Leaving");
}   

void * writer (void * param)
{
    sleep(3);
    printf("\nWriter is trying to enter");
    pthread_mutex_lock(&wsem);
    printf("\nWrite has entered and new data");
    
    pthread_mutex_unlock(&wsem);    
    printf("\nWriter is leaving");
    sleep(10);
    exit(0);
}

int main()
{
    int n1,n2,i;    
    printf("\nEnter the no of readers: ");
    scanf("%d",&n1);
    printf("\nEnter the no of writers: ");
    scanf("%d",&n2);
    
     for(i=0;i<n2;i++)
        pthread_create(&tid,NULL,writer,NULL);
    
    for(i=0;i<n1;i++)
        pthread_create(&tid,NULL,reader,NULL);  

    
    pthread_join(tid,NULL);
	pthread_join(t1,NULL);
    
    sleep(10);
    exit(0);
}

/***********OUTPUT***********/
/*
akshay@akshay-Inspiron-5558:~/Downloads$ gcc ass5.c -lpthread -o re
akshay@akshay-Inspiron-5558:~/Downloads$ ./re

Enter the no of readers: 3

Enter the no of writers: 3

Reader is trying to enter
Reader is trying to enter
1 Reader is inside and data=5
Reader is trying to enter
2 Reader is inside and data=5
3 Reader is inside and data=5
Reader is Leaving
Writer is trying to enter
Writer is trying to enter
Writer is trying to enter
Reader is Leaving
Reader is Leaving
Write has entered and new data=6
Writer is leaving
Write has entered and new data=7
Writer is leaving
Write has entered and new data=8
Writer is leaving
*/
