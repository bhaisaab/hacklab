#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#define N 100
#define THREADS 3
#define debug(x) ;//printf("%s: %d\n", #x, x);

void printmatrix(int* ptr, int i, int j);
void *doCalculate(void *ptr);
int x[N][N], y[N][N], z[N][N];
int a, b, c;

int main(int argc, char *argv[])
{
    int i, j, k;
    pthread_t nothreads[THREADS + 1];
    void *exitstat;
    
    printf("\nEnter number of ROWS & COLUMNS in 1st matrix::\n");
    scanf("%d%d", &a, &b);
    printf("\nEnter number of COLUMNS in 2nd matrix::\n");
    scanf("%d", &c);
    printf("%d,%d,%d", a,b,c);
    printf("\nEnter elements of 1st matrix::\n");
    for(i = 0; i < a; i++)
      for(j = 0; j < b; j++)
        scanf("%d", &x[i][j]);

    printf("\nEnter elements of 2nd matrix::\n");
    for(i = 0; i < b; i++)
      for(j = 0; j < c; j++)
        scanf("%d", &y[i][j]);
    printf("\n1st matrix::\n");
    printmatrix(&x[0][0],a,b);
    printf("\n2nd matrix::\n");
    printmatrix(&y[0][0],b,c);

    //-- thread creation goes here
    for (i = 1; i <= THREADS; i++)
    {
        if (pthread_create(&nothreads[i], NULL, doCalculate, (void *) &i) != 0)
        perror("Thread creation failed");
        sleep(1);
    }

    //-- thread joining goes here
    for (i = 1; i <= THREADS; i++)
    {
        if (pthread_join(nothreads[i], &exitstat) != 0)
        perror("joining failed");
    }
    printf("\nResult of multiplication of 1st & 2nd matrix::\n");    
    printmatrix(&z[0][0], a, c);
    exit(0);
}

//---- this is the function executed by 
//     each thread
void *doCalculate(void *ptr)
{
    int i, j, k;
    int rowsperprocess = (a < THREADS) ? 1: ceil((double)a/THREADS);
    debug(a);
    debug(rowsperprocess);
    int id = *((int *)ptr);
    debug(id);
    int startPoint, endPoint;
    startPoint = (id - 1) * rowsperprocess;
    if (id == THREADS)
    endPoint = startPoint + rowsperprocess + (N % THREADS) - 1;
    else
    endPoint = startPoint + rowsperprocess;

    printf("\e[34mThread%d:\e[00m Rows per thread = %d startpoint = %d and endpoint = %d\n", id, endPoint - startPoint, startPoint, endPoint);
    printf("Calculated row(s)::\n");

    for(i = startPoint; i < endPoint; i++)
    {
      for (j = 0; j < b; j++)
      {
          for (k = 0; k < c; k++)
            z[i][k] += x[i][j] * y[j][k];
      //printf("%5d\t", z[i][k-1]);
      }
      //printf("\n");
    }
    for(i = startPoint; i < endPoint; i++)
    {
      for (k = 0; k < c; k++){
      printf("%5d\t", z[i][k]);
      }
      printf("\n");
    }

}



//-- this will print matrices
void printmatrix(int* m, int i, int j)
{
    int p, q;
    for (p = 0; p < i; p++)
    {
        for (q = 0; q < j; q++)
        printf("%5d\t", m[p *N + q]);
        printf("\n");
    }
    printf("\n");
}

