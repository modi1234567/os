
/* Inter-process Communication using Shared Memory using System V. Application to
demonstrate: Client and Server Programs in which server process creates a shared memory segment and
writes the message to the shared memory segment. Client process reads the message from the shared
memory segment and displays it to the screen.*/

#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
int main()
{	int retval,shmid;
	void *memory=NULL;
	char *p;
	shmid=shmget((key_t)123456789,6,IPC_CREAT|0666);
	if(shmid<0)
	{
		printf("Failure in creation ");
		shmid=shmget((key_t)123456789,6,0666);
	}
	printf("\n We are getting the shared memory created %d \n",shmid);
	memory=shmat(shmid,NULL,0);
	if(memory==NULL)
	{
		printf("\n Attachment failure");
		return 0;
	}
	p=(char *)memory;
	memset(p,'\0',6);
	memcpy(p,"Hello",6);
	
	retval=shmdt(p);
	if(retval<0)
	{
		printf("detachment failure");
		return 0;
	}
}

/*
aniket@aniket-Inspiron-3521:~/Downloads/os$ gcc ass8a.c
aniket@aniket-Inspiron-3521:~/Downloads/os$ ./a.out

 We are getting the shared memory created 6455309 
aniket@aniket-Inspiron-3521:~/Downloads/os$ 

*/

//******************************************* 





#include<sys/shm.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<memory.h>
int main()
{	int retval,shmid;
	void *memory=NULL;
	char *p;
	shmid=shmget((key_t)123456789,6,IPC_CREAT|0666);
	if(shmid<0)
		printf("Failure in creation ");
	
	printf("\n We are getting the shared memory created %d \n",shmid);
	memory=shmat(shmid,NULL,0);
	if(memory==NULL)
	{	printf("\n Attachment failure");
		return 0;
	}
	p=(char *)memory;
	printf("\n MESSAGE is %s \n",p);
	retval=shmdt(p);
	if(retval<0)
	{
		printf("detachment failure");
		return 0;
	}
	retval=shmctl(shmid,IPC_RMID,NULL);
return 0;
}


/*aniket@aniket-Inspiron-3521:~/Downloads/os$ gcc ass8b.c
aniket@aniket-Inspiron-3521:~/Downloads/os$ ./a.out

 We are getting the shared memory created 6389774 

 MESSAGE is hello 
aniket@aniket-Inspiron-3521:~/Downloads/os$
*/

