//g++ -std=c++0x -pthread 372.cpp
//301450082318807027
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <thread>

using namespace std;

mutex m;
unsigned long long sum = 0ULL;
unsigned long long minr = 2e6;
unsigned long long maxr = 1e9;

void
setofy(unsigned long val)
{
  unsigned long long lsum = 0ULL;
  unsigned long long x = minr+1;
  long double t1 = sqrt(val);
  long double t2 = sqrt(val+1);
  long double s1, s2;
  s1=x*t1;
  s2=x*t2;
  for(; x<=maxr; x++,s1+=t1,s2+=t2)
  {
    unsigned long long y2 = s2+1;
    unsigned long long y1 = s1-1;;
    while( (y1*y1) < (x*x*val) ) y1++;
    while( (y2*y2) >= (x*x*(val+1)) ) y2--;
    if(y1>maxr) break;
    if(y2>maxr) y2 = maxr;
    if(y2>=y1) lsum+=(y2-y1+1);
  }
  m.lock();
  sum+=lsum;
  m.unlock();
}

int main()
{
  //printf("enter m, n: ");
  //int i = scanf("%llu %llu", &minr, &maxr);
  printf("M = %llu, N = %llu, sum=%llu\n", minr, maxr, sum);

  unsigned long maxv = floor( (double)( 1.0 * maxr *  maxr / ((minr+1)*(minr+1)) ) );
  unsigned long val = 1ULL;
  unsigned long long x = minr+1;

  int parts = 8;
  thread* tt = new thread[parts];

  printf("[main] using optimized algo till %lu\n", maxv);
  while (val <= maxv)
  {
    for(int i=0; i<parts; ++i) {
      tt[i] = thread(setofy, val);
      val+=2;
      if (val>maxv)
      {
        printf("\nbreaking, val=%lu\n", val);
        parts = i+1;
        break;
      }
    }
    for(int i=0; i<parts;++i)
      tt[i].join();

    printf("sum=%llu\n", sum);
  }
  printf("\n%llu\n", sum);
  delete [] tt;
}
