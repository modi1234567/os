
/*Implement an assignment using File Handling System Calls (Low level system calls like
open, read, write, etc).*/

#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
char buf[32];
void insert()
{
	int fd,l,i,d,j=0;
	//char name[20];
	char  no[10];
	fd=open("nik.txt",O_CREAT|O_RDWR|O_APPEND,0666);
	printf("\nEnter name: ");
	scanf("%s",buf);
	
	l=strlen(buf);
	
	for(i=l;i<20;i++)
		buf[i]='.';
	
	printf("\nbuff=%s\n",buf);
	
	printf("\nEnter Mobile no: ");
	scanf("%s",no);
	printf("\nno=%s\n",no);
	for(i=20;i<30;i++)
	{
		buf[i]=no[j++];
	}
	printf("\nbuff=%s\n",buf);
	buf[i]='\n';
	write(fd,buf,sizeof(buf));
	close(fd);
}
void disp()
{
	int fd;
	fd=open("nik.txt",O_RDONLY);
	if(!read(fd,buf,sizeof(buf)))
		printf("\n NO DATA FOUND");
	else
	{
		printf("\n DATA IN FILE ::\n");
		do
		{
			printf("\n%s",buf);
		}while(read(fd,buf,sizeof(buf)));
	}
	close(fd);
}	
void search()
{
	int fd,i=0,flag=0;
	char name[20];
	printf("\nENter name to be searched : ");
	scanf("%s",name);
	fd=open("nik.txt",O_RDONLY);
	if(!read(fd,buf,sizeof(buf)))
		printf("\n NO DATA FOUND");
	else
	{
		do
		{
			flag=0;
			i=0;
			while(name[i]!='\0')
			{
				
				if(name[i]!=buf[i])
				{
					flag++;
					break;
				}
				i++;
			}
			
			if(flag==0)
			{
				printf("\nDATA FOUND :\n");
				printf("\n%s",buf);
				break;
			}
		}while(read(fd,buf,sizeof(buf)));
		if(flag>0)
		{
			printf("\n NO DATA FOUND in FILE");
		}
	}
	close(fd);
}
void modify()
{
	int fd,i=0,flag=0,choice;
	char name[20];
	printf("\nENter name to be modified : ");
	scanf("%s",name);
	fd=open("nik.txt",O_RDWR,0777);
	if(!read(fd,buf,sizeof(buf)))
		printf("\n NO DATA FOUND");
	else
	{
		do
		{
			flag=0;
			i=0;
			while(name[i]!='\0')
			{
				
				if(name[i]!=buf[i])
				{
					flag++;
					break;
				}
				i++;
			}
			
			if(flag==0)
			{
				int l,i;
				printf("\nDATA FOUND :\n");
				printf("\n%s",buf);
				do
				{
					printf("\nENter choice :\n1)Change NAME\n2)Change Mobile no\n3)Exit\n");
					scanf("%d",&choice);
					switch(choice)
					{
						case 1:printf("Enter NEW name: ");
								scanf("%s",name);
								lseek(fd,-sizeof(buf),SEEK_CUR);
								l=strlen(name);
								for(i=0;i<l;i++)
									buf[i]=name[i];
								for(i=l;i<20;i++)
									buf[i]='.';
								printf("\nbuff=%s\n",buf);
								write(fd,buf,sizeof(buf));
								printf("\nMdification made");
								break;
						case 2:printf("Enter NEW Mobile no: ");
								scanf("%s",name);
								lseek(fd,-sizeof(buf),SEEK_CUR);
								l=strlen(name);
								int j=0;
								for(i=20,j=0;j<l;i++,j++)
									buf[i]=name[j];
								printf("\nbuff=%s\n",buf);
								write(fd,buf,sizeof(buf));
								printf("\nMdification made");
								break;
					}
				}while(choice!=3);
				break;
			}
		}while(read(fd,buf,sizeof(buf)));
		if(flag>0)
		{
			printf("\n NO DATA FOUND in FILE");
		}
	}
	close(fd);
}
void delete()
{
	int fd1,fd2,i=0,flag=0;
	char name[20];
	printf("\nENter name to be deleted : ");
	scanf("%s",name);
	fd2=open("bhuj.txt",O_CREAT,0777);
	close(fd2);
	fd1=open("nik.txt",O_RDONLY);
	
	if(!read(fd1,buf,sizeof(buf)))
		printf("\n NO DATA FOUND");
	else
	{
		fd2=open("bhuj.txt",O_RDWR|O_EXCL|O_APPEND,0777);
		do
		{
			flag=0;
			i=0;
			while(name[i]!='\0')
			{
				
				if(name[i]!=buf[i])
				{
					flag++;
					break;
				}
				i++;
			}
			
			if(flag!=0)
			{
				write(fd2,buf,sizeof(buf));
			}
		}while(read(fd1,buf,sizeof(buf)));
		remove("nik.txt");
		rename("bhuj.txt","nik.txt");
		printf("\ndata deleted successfully");
		close(fd2);
	}
	close(fd1);
}
int main()
{
	do
	{
		int choice;
		
		printf("\n1)insert\n2)display\n3)search\n4)Modify\n5)Delete\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:insert();break;
			case 2:disp();break;
			case 3:search();break;
			case 4:modify();break;
			case 5:delete();break;
		}
	}while(1);
}
