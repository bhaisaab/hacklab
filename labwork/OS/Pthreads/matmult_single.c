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

int main(int argc, char* argv[])
{
  int Am, An, Bn, Bo; /* An defined above, A[m][n] B[n][o]*/
  register int i, j, k;

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

  /* Make M*O pThreads */
  for( i = 0; i < Am; i++ )
    for( j = 0; j < Bo; j++ )
      for( k = 0; k < An; k++ )
        C[i][j] += A[i][k]*B[k][j];	

  /* Print Result*/
  for( i = 0; i < Am; i++ ){
    for( j = 0; j < Bo; j++ )
      printf("%d  ",C[i][j]);
    printf("\n");
  }  

  return 0;
}

