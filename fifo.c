
/* FIFOs: Full duplex communication between two independent processes. First process accepts
sentences and writes on one pipe to be read by second process and second process counts
number of characters, number of words and number of lines in accepted sentences, writes this
output in a text file and writes the contents of the file on second pipe to be read by first process
and displays on standard output.*/

 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define FIFO1 "fifo_1"
#define FIFO2 "fifo_2"

int main()
{
	char buf[100],buf1[100];
	int fd,fd1;
	
	printf("\nEnter a string\n");
	scanf("%[^0]",buf);// it will accept strings until user enters 0
	
	mkfifo(FIFO1,0666);
	fd=open(FIFO1,O_WRONLY);

	write(fd,buf,100);
	printf("\nMessage sent");
	unlink(FIFO1);
	fd1=open(FIFO2,O_RDONLY);
	read(fd1,buf1,sizeof(buf1)+1);
	printf("\nMessage received");
	printf("\n%s",buf1);
	
	return 0;
}
/*
pranav@Jarvis:~/Documents$ cc fifo1.c
pranav@Jarvis:~/Documents$ ./a.out

Enter a string
nik hgfh
sds ghg
wd gff0******

Message sent
Message received

Characters = 23.
Words = 6.
Lines = 3.pranav@Jarvis:~/Documents$ 
*/

//***************************************************below code belongs to another file fifo2.c***********



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define FIFO1 "fifo_1"
#define FIFO2 "fifo_2"

int main()
{
	char buf[100],buf1[100];
	int fd,fd1;
	int words,lines,characters,len,i;
	char ch;
	FILE *fp;
	fd=open(FIFO1,O_RDONLY);
	read(fd,buf,100);
	printf("\nMessage received");
	printf("\n%s",buf);
	len=strlen(buf);

	words=1;
	lines=1;
	characters=0;
	for(i=0;i < len;i++)
	{
		if(buf[i] == ' ' || buf[i] == '.' || buf[i] == '\n')
			words++;
	    if(buf[i] == '.' || buf[i] == '\n')
			lines++;
	}
	characters=strlen(buf);
	printf("\nCharacters = %d ",characters);
	printf("\nWords = %d ",words);
	printf("\nLines = %d ",lines);

	fp=fopen("abc.txt","w");
	fprintf(fp,"\nCharacters = %d.",characters);
	fprintf(fp,"\nWords = %d.",words);
	fprintf(fp,"\nLines = %d.",lines);
	fclose(fp);
	fp=fopen("abc.txt","r");
	i=0;
	while((ch=fgetc(fp)) != EOF)
	{
		buf1[i]=ch;
		i++;
	}	
	printf("\nBuffer contents\n");
	printf("\n%s",buf1);
	fclose(fp);
	unlink(FIFO1);
	mkfifo(FIFO2,0666);
	fd1=open(FIFO2,O_WRONLY);
	write(fd1,buf1,sizeof(buf1)+1);
	printf("\nMessage sent");
	
        return 0;
}
/*
pranav@Jarvis:~/Documents$ cc fifo2.c
pranav@Jarvis:~/Documents$ ./a.out

Message received
nik hgfh
sds ghg
wd gff
Characters = 23 
Words = 6 
Lines = 3 
Buffer contents


Characters = 23.
Words = 6.
Lines = 3.
Message sentpranav@Jarvis:~/Documents$ 
*/
