/*************************************************************************
 * matmult_threaded.c: Multithreaded Matrix Multiplication using Pthreads
 * Date: 14 September 2009
 * Author: Rohit Yadav<rohityadav89@gmail.com>
 *         (IDD 07020003) for Operating Systems Lab
 * Compile using: gcc -lpthread -Wall matmult_threaded.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_SIZE 1000

typedef int Array;

Array A[MAX_SIZE][MAX_SIZE];
Array B[MAX_SIZE][MAX_SIZE];
static Array C[MAX_SIZE][MAX_SIZE];

typedef struct{
  int i;  int j;
}Pos;

int Am, An, Bn, Bo;

/* A thread outputs an element 
void* MultiplyMatrixByElement(void *pos)
{
  int i = ((Pos*)pos)->i;
  int j = ((Pos*)pos)->j;
  register int p;

	for( p = 0; p < An; p++ )
    C[i][j] += A[i][p]*B[p][j];	
   pthread_exit(0);
}
*/
/* A thread outputs a row */
void* MultiplyMatrixByRow(void *pos)
{
  int i = ((Pos*)pos)->i; /* Row */
  int j = ((Pos*)pos)->j; /* Col */
  register int p, q;

	for( p = 0; p < j; p++ )
    for( q = 0; q < An; q++ )	
      C[i][p] += A[i][q]*B[q][p];	
   pthread_exit(0);
}

int main(int argc, char* argv[])
{
  register int i, j;
  int tid_c = 0;
  int scope;

  /* pThread identifiers */
  pthread_t tid[MAX_SIZE]; 
  /* set of thread attributes */
  pthread_attr_t attr;
  /* get the default attributes */	
  pthread_attr_init(&attr);

  freopen("/home/rohit/input", "r", stdin);

  scanf("%d %d",&Am,&An);
  for( i = 0; i < Am; i++ )
    for( j = 0; j < An; j++ )
      scanf("%d", &A[i][j]);

  scanf("%d %d", &Bn, &Bo);
  if(An != Bn){
    printf("Size Mismatch! Retry.\n");
    exit(1); 
  }
  else
    for( i = 0; i < Bn; i++ )
      for( j = 0; j < Bo; j++ )
        scanf("%d",&B[i][j]);

  /* Initiate Threading procedure */
  pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM);

  /* Make M pThreads */
  for( i = 0; i < Am; i++ )
    {
      Pos *pos = (Pos *)malloc(sizeof(Pos));
      pos->i = i; pos->j = Bo;
      pthread_create( &tid[tid_c++], &attr, MultiplyMatrixByRow, (void *)pos);
    }

  for( i = 0; i < (Am); i++ )
    if( pthread_join( tid[i], NULL ) != 0 )
    {
      printf("Error");
      return EXIT_FAILURE;
    }

  /* Print Result */
  for( i = 0; i < Am; i++ ){
    for( j = 0; j < Bo; j++ )
      printf("%d  ",C[i][j]);
    printf("\n");
  }  
  return 0;
}

