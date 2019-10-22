
/*	
Statement: Implement matrix multiplication using multithreading. 
Application should have pthread_create, pthread_join, pthread_exit. In the program, every thread must return 
the value and must be collected in pthread_join in the main function. Final sum of row-column multiplication must be done by main thread (main function)
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define MAX 10
typedef struct Data
{
	int Row, Col,n;
}Data;

int A[MAX][MAX], B[MAX][MAX], Ans[MAX][MAX];
void* TFunc(void *arg)
{
	Data *data;
	int ans,row,col,cnt,n;
	int *t;
	data = (Data *)arg;
	t = (int *) malloc(sizeof(int));
	row = data->Row;
	col = data->Col;
	n = data->n;
	ans=0;
	
	for(cnt=0;cnt<n;cnt++ )
		ans += A[row][cnt] * B[cnt][col];

	*t = ans;
	pthread_exit((void *)t);
}


int main(int argc, char *argv[])
{
	pthread_t id[MAX * MAX];
	int Row1, Col1, Row2, Col2, cnt, cnt1,cnt2;
	Data d[MAX * MAX];
	int *t;
	printf("\n\t Enter the size of matrix1 (Row Col) : ");
	scanf(" %d %d", &Row1, &Col1);
	printf("\n\t Enter the data of matrix1 : \n");
	for(cnt=0;cnt < Row1 ; cnt++)
	{
		printf("\t");
		for(cnt1=0;cnt1 < Col1; cnt1++)
		{
			scanf(" %d", &A[cnt][cnt1]);
		}
	}
	
	printf("\n\t Enter the size of matrix2 (Row Col) : ");
	scanf(" %d %d", &Row2, &Col2);
	printf("\n\t Enter the data of matrix2 : \n");
	for(cnt=0;cnt < Row2 ; cnt++)
	{
		printf("\t");
		for(cnt1=0;cnt1 < Col2; cnt1++)
		{
			scanf(" %d", &B[cnt][cnt1]);
		}
	}
	
	cnt2 =0;
	for(cnt=0;cnt < Row1 ; cnt++)
	{
		for(cnt1=0;cnt1 < Col2; cnt1++)
		{
			d[cnt2].Row = cnt;
			d[cnt2].Col = cnt1;
			d[cnt2].n = Col1;
			pthread_create(&id[cnt2], NULL, TFunc, (void *)&d[cnt2]);
			pthread_join(id[cnt2],(void **)&t);
			Ans[cnt][cnt1] = *(t);
			cnt2++;
		}
	}
	
	printf("\n\t Answer : ");
	for(cnt=0;cnt < Row1 ; cnt++)
	{
		printf("\n\t ");
		for(cnt1=0;cnt1 < Col2; cnt1++)
		{
			printf(" %d", Ans[cnt][cnt1]);
		}
	}
	printf("\n\n");	
}
/*

		Output

1.
	 Enter the size of matrix1 (Row Col) : 2 2

	 Enter the data of matrix1 : 
	1 2
	3 4

	 Enter the size of matrix2 (Row Col) : 2 2

	 Enter the data of matrix2 : 
	1 2
	3 4

	 Answer : 
	  7 10
	  15 22

	------------------------------------------------------------------------
2.
	 Enter the size of matrix1 (Row Col) : 2 3

	 Enter the data of matrix1 : 
	1 2 3
	4 5 6

	 Enter the size of matrix2 (Row Col) : 3 2

	 Enter the data of matrix2 : 
	1 2
	3 4
	5 6

	 Answer : 
	  22 28
	  49 64
*/
