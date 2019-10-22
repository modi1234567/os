#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
	pid_tpid;
	pid=fork();
	if(pid==0)
	{
		while(1)
		{
			printf("\nIn Child process\n");
			printf("\nChild process Id=%d\tParent process Id=%d\n",getpid(),getppid());
			sleep(30);
		}
	}
	else
	{
		//sleep(5);
		printf("\nIn Parent process\n");
		printf("\nParent process Id=%d\n",getpid());
	}
	return 0;
}

/* OUTPUT

localhost@ubuntu16:~/OS/assignment1$ gccorphan.c
localhost@ubuntu16:~/OS/assignment1$ ./a.out

In Child process

Child process Id=4934	Parent process Id=4933

In Parent process

Parent process Id=4933
localhost@ubuntu16:~/OS/assignment1$ 
In Child process

Child process Id=4934	Parent process Id=1477

In Child process

Child process Id=4934	Parent process Id=1477

*/

