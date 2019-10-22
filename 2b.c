#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
void Merge_Sort(int *array,int first,int last);
void merge(int *array,int start,int mid,int end);

void main(int argc,char* argv[])
{

        if (argc <= 2)  
        {
             fprintf(stderr, "Usage: %s <file-to-exec>\n", argv[0]);
              exit(EXIT_FAILURE);
        }

	int total,array[20],i,key,result;
	char *newenviron[] = { NULL };
	char **newargv ;

   	/*printf("\nEnter no of elements to be sorted");
   	scanf("%d",&total);
   	printf("\nEnter the %d elements ",total);*/
   	printf("\nEnter the %d elements ",argc);
	for(i=2;i<argc;i++)
        {
           //scanf("%d",&array[i]);
		printf("%s",argv[i]);
        }
        for(i=2;i<argc;i++)
        {
           //scanf("%d",&array[i]);
		array[i-2]=atoi(argv[i]);
        }
	printf("out of for");
	for(i=0;i<argc-2;i++)
        {
           //scanf("%d",&array[i]);
		printf("%d ",array[i]);
        }
	total=argc-2;
	// char a1[total][20];
        newargv=(char**)malloc(sizeof(char*)*(total+1));
        for(i=0;i<total;i++)
        	newargv[i]=(char*)malloc(20);
        
        Merge_Sort(array,0,total-1);
        for(i=0;i<total;i++)
        	sprintf(newargv[i],"%d",array[i]);
         
     	newargv[i]=NULL;
        int pid=fork();
        if(pid==0)
        {	
        	
    	       	execve(argv[1], newargv, newenviron);
               perror("execve"); 
               exit(EXIT_FAILURE);
        
	}
	
	  wait(NULL);
}

void merge(int *array,int start,int mid,int end)
{
  int end1,end2,start1,start2,temp[20],i,j;
  start1=start;
  start2=mid+1;
  end1=mid;
  end2=end;
  i=start;
  while(start1<=end1 && start2<=end2)
  {
    if(array[start1]<array[start2])
    {
     temp[i]=array[start1];
     start1++;
     i++;
    }
    
    
   else if(array[start1]>array[start2])
    {
     temp[i]=array[start2];
     start2++;
     i++;
    }
    
    
   else if(array[start1]==array[start2])
    {
     temp[i++]=array[start1];
     temp[i++]=array[start2];
     start1++;
     start2++;
     
    }
    
  }
  
   while(start1<=end1)
   {
   temp[i]=array[start1];
   start1++;
   i++;
   
   }
   
   while(start2<=end2)
   {
   temp[i]=array[start2];
   start2++;
   i++;
   
   }
   for(j=start;j<=end;j++)
   array[j]=temp[j];
}

void Merge_Sort(int *array,int first,int last)
{
  int mid;
  if (first < last)
  {
  	mid=(first+last)/2;
  	Merge_Sort(array,first,mid);
  	Merge_Sort(array,mid+1,last);
  	merge(array,first,mid,last);
  }
}



// below code belongs to another program 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int Binary_search(int *array,int first,int last,int key)
{
        int mid;
	while(first<=last)
	{

           mid=(first+last)/2;
           if(array[mid]==key)
           	return mid;
           else if(array[mid]>key)
		last=mid-1;
	  else if(array[mid]<key)
		first=mid+1;
	}
	return -1;

}

void main(int argc ,char *argv[])
{
     int array1[20],i,res,key;
     for(i=0;i<argc;i++)
     	array1[i]=atoi(argv[i]);
     	
     	for(i=0;i<argc;i++)
     	printf("  %d",array1[i]);
     
     	printf("\n Enter the key to be search ");
     	scanf("%d",&key);
     res=Binary_search(array1,0,argc-1,key);
     if(res==-1)
     	printf("\n Not Found");
     else
     	printf("\n Found");
}




