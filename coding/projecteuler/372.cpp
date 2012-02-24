//g++ -std=c++0x -pthread 372.cpp
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <thread>
using namespace std;

//301450082318808109
mutex m;
unsigned long long sum = 0ULL;
unsigned long long minr = 2000000ULL;
unsigned long long maxr = 1000000000ULL;

//unsigned long long

void brute(unsigned long long x)
{
  unsigned long long lsum = 1ULL;
  //unsigned long long x = minr+1;
  //while (x <= maxr)
  //{
    printf("x=%llu\n", x);
    unsigned long long y = x+1;
    while (y <= maxr)
    {
      if (((unsigned long long)(( 1.0*y*y/(x*x))) % 2) == 1)
        ++lsum;
      ++y;
    }
    //++x;
    m.lock();
    sum+=lsum;
    m.unlock();
  //}
}

void cmb(unsigned long long val)
{
  printf("val=%llu\n",val);
  unsigned long long lsum = 0ULL;
  double sqrtv = sqrt(val);
  double sqrtv1 = sqrt(val+1);
  unsigned long long x = minr+1;
  unsigned long long xmax = ceil(maxr/sqrtv);

  while (x<=xmax)
  {
    unsigned long long y = ceil(x*sqrtv);
    if (y > maxr) {
      x+=1L;
      continue;
    }
    double yn = (x*sqrtv1);
    if ((yn - floor(yn)) == 0.0F)
      yn=yn-1.0;
    unsigned long long y1 = floor(yn);
    if (y1 > maxr)
      y1 = maxr;
    x+=1;
    if (y1 >= y)
      lsum+=(y1-y+1);
  }
  m.lock();
  sum+=lsum;
  m.unlock();
}

void R()
{
  unsigned long long maxv = 1.0 * (double)( maxr *  maxr / ((minr+1)*(minr+1)) );
  unsigned long long lsum = 0ULL;
  unsigned long long val = 1ULL;
  while (val <= maxv) {
 //  lsum+=cmb(val);
   val+=2;
  } 
  sum = lsum;
}

int main()
{
//  printf("enter m, n: ");
//  int i = scanf("%llu %llu", &minr, &maxr);
  printf("M = %llu, N = %llu\n", minr, maxr);
  int parts = 8;
  thread* tt = new thread[parts];
  unsigned long long maxv = floor( (double)( 1.0 * maxr *  maxr / ((minr+1)*(minr+1)) ) );
  unsigned long long val = 1ULL;
  unsigned long long x = minr+1;

#if 0
  printf("[main] using optimized algo\n");
  while (val <= maxv)
  {
    for(int i=0; i<parts; ++i) {
      tt[i] = thread(cmb, val);
      val+=2;
      if (val>maxr)
      {
        parts = i+1;
        break;
      }
    }
    for(int i=0; i<parts;++i)
      tt[i].join();
    printf("\r%f%% done", val * 100.0 / maxv);
  }
#else
  //Brute force
  printf("[main] using brute force\n");
  while (x <= maxr)
  {
    for(int i=0; i<parts; ++i) {
      tt[i] = thread(brute, x);
      ++x;//val+=2;
      if (x>maxr)
      {
        parts = i+1;
        break;
      }
    }
    for(int i=0; i<parts;++i)
      tt[i].join();
    printf("\r%f%% done", x * 100.0 / maxr);
  }
#endif

  printf("\n%lld\n", sum);
  delete [] tt;
}
