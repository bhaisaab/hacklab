#include<stdio.h>
#include<pthread.h>
#include<iostream>
#include<unistd.h>
#include<stdlib.h>

#define MAX 500
using namespace std;
unsigned long long result[MAX];
int fibo[2][2] = {{1, 1},{1, 0}};
unsigned long long temp[2][2] = {{1l, 1l},{1l, 0l}};
unsigned long long res[2][2];

/*
(pos1)1 (pos2)1  ^ n = fn fn+1
(pos3)1 (pos4)0        fn+1 fn-1

*/

/* A thread outputs an element  */
void* MultiplyMatrixByElement(void *pos)
{
  int i;
  int j;
  switch(*(int*)pos)
  {
    case 1:  i = 0; j = 0; break;
    case 2:  i = 0; j = 1; break;
    case 3:  i = 1; j = 0; break;
    case 4:  i = 1; j = 1; break;
  }
  register int p;

  res[i][j] = 0ll;
  for( p = 0; p < 2; p++ )
    res[i][j] += fibo[i][p]*temp[p][j];	
   pthread_exit(0);
}

int genFibo(int n)
{
  register int globalCounter = 2;
  result[0] = 0ll;
  result[1] = 1ll;

  n-=2;

  while(n > 0)
  {
  register int i, j;
  int tid_c = 0;

  /* pThread identifiers */
  pthread_t tid[4]; 
  /* set of thread attributes */
  pthread_attr_t attr;
  /* get the default attributes */	
  pthread_attr_init(&attr);

  int pos[4] = {1, 2, 3, 4};
  /* Make M pThreads */
  for( i = 0; i < 4; i++ )
    {
      pthread_create( &tid[tid_c++], &attr, MultiplyMatrixByElement, (void *)&pos[i]);
    }

  /*Wait...*/
  for( i = 0; i < 4; i++ )
    if( pthread_join( tid[i], NULL ) != 0 )
    {
      printf("Error");
      return EXIT_FAILURE;
    }
  result[globalCounter++] = res[0][1];
  /* Copy to temp */
  temp[0][0] = res[0][0];
  temp[0][1] = res[0][1];
  temp[1][0] = res[1][0];
  temp[1][1] = res[1][1];
  n--;
  }
}


int main()
{
	int total;
        freopen("/home/rohit/input", "r", stdin);
        scanf("%d", &total);

        if (total < 2)
          return 1;
        if(total < MAX)
        genFibo(total);
	//printf("this is the parent thread and the fibonnaci series is\n");
	//for(int j=0;j<total;j++)
	//{
	//	printf("%lld \t", result[j]);
	//}
	//cout<<endl;
	return 0;
}
