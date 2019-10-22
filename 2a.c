
/*Implement the C program in which main program accepts the integers to be sorted.
Main program uses the fork system call to create a new process called a child process.
Parent process sorts the integers using merge sort and waits for child process using wait
system call to sort the integers using quick sort. Also demonstrate zombie and orphan
states.


*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void QuickSort(int Arr[],int First, int Last)
{
	if(First < Last)
	{
		int pivote = Arr[First];
		int cnt1, cnt2,temp;
		cnt1 = First +1;
		cnt2 = Last;
		do
		{
			while((Arr[cnt1] < pivote) && (cnt1 <= Last) )
			cnt1++;
			while((Arr[cnt2] > pivote) && (cnt2 >= First) )
			cnt2--;
			if( cnt1 < cnt2)
			{
			temp = Arr[cnt2];
			Arr[cnt2] = Arr[cnt1];
			Arr[cnt1] = temp;
			}
		}while( cnt1 < cnt2);
		if(cnt2 != First)
		{
			Arr[First] = Arr[cnt2];
			Arr[cnt2] = pivote;
		}
		QuickSort(Arr, First, cnt2);
		QuickSort(Arr, cnt2+1, Last);
	}
}

void Merge(int Arr[],int First, int mid, int Last)
{
	int cnt,cnt1, cnt2, Temp[MAX];
	cnt=0;
	cnt1 = First;
	cnt2=mid+1;
	while( (cnt1 <= mid) && (cnt2 <= Last))
	{
		if(Arr[cnt1] < Arr[cnt2])
		{
		Temp[cnt++] = Arr[cnt1];
		cnt1++;
		}
		else
		{
		Temp[cnt++] = Arr[cnt2];
		cnt2++;
		}
	}
	while(cnt1 <=mid )
	{
		Temp[cnt++] = Arr[cnt1];
		cnt1++;
	}
	while(cnt2 <= Last)
	{
		Temp[cnt++] = Arr[cnt2];
		cnt2++;
	}
	for(cnt1 =0; cnt1 < cnt; cnt1++)
	{
		Arr[First + cnt1] = Temp[cnt1];
	}
}

void MergeSort(int Arr[],int First, int Last)
{
	if(First < Last)
	{
		int mid,cnt;
		mid= (First + Last)/2;
		MergeSort(Arr, First,mid);
		MergeSort(Arr, mid+1 , Last);
		Merge(Arr, First, mid, Last);
	}
}

int main()
{
	int ID;
	int Arr[MAX], n, cnt;

	printf("\n\t Enter the number of elements in array: ");
	scanf(" %d", &n);

	printf("\n\t Enter the array elements: ");
	for(cnt =0;cnt < n; cnt++)
	{
		scanf(" %d", &Arr[cnt]);
	}

	ID = fork();
	if(ID < 0)
	{
		printf("\n\t Process Not created");
	}
	else if (ID == 0)
	{
		printf("\n\t In child process");
		QuickSort(Arr,0,n-1);
		printf("\n\t Final Array elements (Sorted By Child): ");
		for(cnt =0;cnt < n; cnt++)
		{
			printf(" %d,", Arr[cnt]);
		}
	}
	else
	{
		wait(NULL);
		printf("\n\n\n\t In parent process");

		MergeSort(Arr,0,n-1);

		printf("\n\t Final Array elements (Sorted By Parent): ");
		for(cnt =0;cnt < n; cnt++)
		{
		printf(" %d,", Arr[cnt]);
		}
	}
	return 0;
}

/* OUTPUT

neeraj@ubuntu:~/Neeraj/OS$ gcc assi1.c
neeraj@ubuntu:~/Neeraj/OS$ ./a.out

Enter the number of elements in array: 10

Enter the array elements: 8
2
7
4
3
6
10
1
15
50

In child process
Final Array elements (Sorted By Child):  1, 2, 3, 4, 6, 7, 8, 10, 15, 50

In parent process
Final Array elements (Sorted By Parent):  1, 2, 3, 4, 6, 7, 8, 10, 15, 50
neeraj@ubuntu:~/Neeraj/OS$
*/
