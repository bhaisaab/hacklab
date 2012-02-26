//g++ -std=c++0x -pthread 372.cpp
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <thread>

#define SQLIM 300000

using namespace std;

mutex m;
unsigned long long sum = 0ULL;
unsigned long long minr = 2000000ULL;
unsigned long long maxr = 1000000000ULL;
double sqrts[SQLIM];

void
setofy(unsigned long val)
{
  unsigned long long lsum = 0ULL;
  unsigned long long x = minr+1;
  unsigned long long lim = maxr/sqrts[val];

  while (x<=lim)
  {
    uint64_t y2 = ceil((x*sqrts[val+1])-1);
    uint64_t y1 = ceil(x*sqrts[val]);
    if(y1>maxr) break;
    if(y2>maxr) y2 = maxr;
    if((y2-y1) >= 0)
      lsum += (y2-y1+1);
    else printf("shucks, x=%llu, val=%lu\n", x, val);
    x++;
  }
  m.lock();
  sum+=lsum;
  m.unlock();
}

int main()
{
  printf("enter m, n: ");
  int i = scanf("%llu %llu", &minr, &maxr);
  printf("M = %llu, N = %llu, sum=%llu\n", minr, maxr, sum);

  unsigned long maxv = floor( (double)( 1.0 * maxr *  maxr / ((minr+1)*(minr+1)) ) );
  unsigned long val = 1ULL;
  unsigned long long x = minr+1;

  for(int i=1; i<=(maxv+10); ++i)
    sqrts[i] = sqrt(i);

  int parts = 8;
  thread* tt = new thread[parts];

  printf("[main] using optimized algo\n");
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
    printf("\r%llu, %f%% done", sum, val * 100.0 / maxv);
  }
  printf("\n%llu\n", sum);
  delete [] tt;
}
