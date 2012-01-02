/*
  Vol1 151 Power Crisis
  Rohit Yadav <rohityadav89@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WELLINGTON 12
#define LIMIT 100
#define ON  1
#define OFF 0

#define cityPower() for(i=0; i<N; i++) printf("|%2d", city[i]); printf("|\n\n");
#define cityNumber() for(i=0; i<N; i++) printf("|\x1B[31m%02d\x1B[00m", i+1); printf("|\n");

#define cityStatus() cityNumber(); cityPower();

int getNextCity(int* city, int cur, int N, int m)
{
  int t; /* Location of Next City */
  int next;
  city[cur] = OFF;

  int i;

  while(m)
  {
    m--;
    t = 0;
    while(1)
    {
      t++;
      next = (cur + t) % N;      
 //     printf("pos: %d\n", t);
      if(city[next] == ON) break; /* Next Lit up City Found */
    }
   // printf("cur= %d\n", t);
   // cityStatus();
    cur = next;
  }
  return next;
}

int main()
{
  int N;
  int city[LIMIT];
  int m;
  int curCity;
  int blackedOut;

  //scanf("%d", &N);
  N = 13;
  while(N < 101)
  {
    m = 1;
    
    int i;
    for(i = 0; i < LIMIT; i++)
      city[i] = ON;
    blackedOut = 0;
    curCity = 0;

    while(blackedOut < N)
    { 
      if(curCity == WELLINGTON)
      { //printf("m=%d IN weell..\n", m);
        //cityStatus();
        if(blackedOut == N-1) 
          break;
      
        blackedOut = 0; 
        ++m; 
        curCity = 0; 
        for(i=0; i < N; i++)
          city[i] = ON;
        continue;
      }
     // printf("m: %d:\n", m);
      curCity = getNextCity(city, curCity, N, m);
      blackedOut++;
    }
    printf("%d, ", m);
    //scanf("%d", &N); 
N++;  
  }
  return 0;
}

