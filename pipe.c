
/*
	Pipes: Full duplex communication between parent and child processes. Parent process
	writes a pathname of a file (the contents of the file are desired) on one pipe to be read
	by child process and child process writes the contents of the file on second pipe to be
	read by parent process and displays on standard output.


*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#define MAX 100
#define read_end 0
#define write_end 1

int main()
{
	pid_t pid;
	int fd1[2],fd2[2];			
	char write_msg[MAX];
	char read_msg[MAX];
	int i;
	FILE *fp;
	char ch;
	if((pipe(fd1) == -1) || (pipe(fd2) == -1))		
	{
		printf("\nERROR : FAILED TO CREATE A PIPE \n");
	}
	else
	{
		pid=fork();  					
		if(pid < 0)						
		{
			printf("\nERROR : FAILED TO CREATE A CHILD PROCESS \n");
		}
		else if(pid > 0)				
		{
			printf("\nEnter the file le name to be read : \n");	
			scanf(" %s",write_msg);
			write(fd1[write_end],write_msg,sizeof(write_msg)+1);		
			close(fd1[write_end]);
			read(fd2[read_end],read_msg,sizeof(read_msg)+1);		
			close(fd2[read_end]); 
			printf("\nThe contents of the file are as follows : \n");	
			printf("%s",read_msg);
			//wait(NULL);
		}
		else if(pid == 0)			
		{
			read(fd1[read_end],read_msg,sizeof(read_msg)+1);	
			close(fd1[read_end]);
			printf("\nName of the file to be read is %s \n",read_msg);
			fp=fopen(read_msg,"r");		
			i=0;			
			while((ch = fgetc(fp)) != EOF )			
			{
				write_msg[i]=ch;
				i++;
			}
			write(fd2[write_end],write_msg,sizeof(write_msg)+1);		
			close(fd2[write_end]);
		}
	}		

	return 0;
}

/*
			OUPUT
neeraj@neeraj:~/neeraj/os/assignment 5$ ./a.out 

Enter the file name to be read : 
abc.txt

Name of the file to be read is abc.txt 

The contents of the file are as follows : 
HI,WHERE DO YOU LIVE?
I LIVE IN PUNE.


*/
