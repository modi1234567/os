/*
	Statement:Deadlock Avoidance Using Semaphores:
Implement the deadlock-free solution to Dining Philosophers problem to illustrate the problem of deadlock and/or starvation that can occur when many synchronized threads are competing for limited resources.
	
	
*/

# include<stdio.h>
# include<stdlib.h>
# include<semaphore.h>
# include<pthread.h>
# include<unistd.h>
# include<ctype.h>
# include<sys/types.h>
# include<sys/wait.h>
# include<sys/sem.h>
sem_t chopstick[5];
int n;
void *thread_func(void* nofi)            
{ 
	int no=(int) nofi;
	while(1)
	{
		while(1)
		{
			sem_wait(&chopstick[no]);			
			if(!sem_trywait(&chopstick[(no+1)%n])) 
			break;
			else
			sem_post(&chopstick[no]);  
		}
		printf("\nPhilosopher %d -> Begin eating",no);
		sleep(2);
		printf("\nPhilosopher %d -> Finish eating\n",no);
		sem_post(&chopstick[no]);                        
		sem_post(&chopstick[(no+1)%n]);
		sleep(3);
		break;
	}
	pthread_exit(NULL);
}

int main()
{
	int i,res;
	pthread_t a_thread[5];

	printf("Enter the number of philosophers : ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		res=sem_init(&chopstick[i],0,1);
		if(res==-1)
		{
			perror("semaphore initialization failed");
			exit(1);
		}
	}
	for(i=0;i<n;i++)
	{
		res=pthread_create(&a_thread[i],NULL,thread_func,(void*) i);
		if(res!=0)
		{
		perror("semaphore creation failed");
		exit(1);
		}

	}
	for(i=0;i<n;i++)
	{
		res=pthread_join(a_thread[i],NULL);
		if(res!=0)
		{
			perror("semaphore join failed");
			exit(1);
		}
	}
	printf("\n \n thread join succesfull\n");
	/*for(i=0;i<n;i++)
	{
		res=sem_destroy(&chopstick[i]);
		if(res==-1)
		{
		perror("semaphore destruction failed");
		exit(1);
		}
	}*/
	exit(0);
}

/**********OUTPUT*****************************************
neeraj@ubuntu:~$ cd Documents/OS/Assignment-No-4
neeraj@ubuntu:~/Documents/OS/Assignment-No-4$ gcc diningfinal.c -lpthread
neeraj@ubuntu:~/Documents/OS/Assignment-No-4$ ./a.out
Enter the number of philosophers : 5

Philosopher 0 -> Begin eating
Philosopher 3 -> Begin eating
Philosopher 3 -> Finish eating

Philosopher 0 -> Finish eating

Philosopher 2 -> Begin eating
Philosopher 4 -> Begin eating
Philosopher 4 -> Finish eating

Philosopher 2 -> Finish eating

Philosopher 1 -> Begin eating
Philosopher 1 -> Finish eating


thread join succesfull
neeraj@ubuntu:~/Documents/OS/Assignment-No-4$ 
*/
