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
		printf("\nIn Child process\n");
		printf("\nChild process Id=%d\n",getpid());
	}
	else
	{
		sleep(30);
		printf("\nIn Parent process\n");
		printf("\nParent process Id=%d\n",getpid());
	}
	return 0;
}

/* OUTPUT

bash-4.2$ gcczombie.c
bash-4.2$ ./a.out

In Child process

Child process Id=2791

In Parent process

Parent process Id=2790

1 Z  1000  2791  2790  0  80   0 -     0 exit   pts/0    00


*/

