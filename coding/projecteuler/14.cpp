/*#include <hash_map> Depreciated, use c++0x
g++ -std=c++0x 14.cpp
*/
#include <unordered_map>
#include <cstdio>
#include <cassert>
using namespace std;

unordered_map<unsigned int, unsigned int> dp;

long f(long n)
{
  assert(n>0);
  if(n==1) return 1;
  if((n%2)==0) return n/2;
  else return 3*n+1;
}


//zeroes eveyone
#define LIM 1000000
static int dpa[LIM];

long
chain(long n)
{
  if((n < LIM) && dpa[n]) return dpa[n];
  int c = 1;
  long norg = n;
  while(n!=1)
  {
    n = f(n);
    if((n < LIM) && (norg < LIM) &&  dpa[n])
    {
      dpa[norg] = c+dpa[n];
      return dpa[norg];
    }
    c+=1;
    if(norg < LIM)
      dpa[norg] = c;
  }
  return c;
}

long
chainDPHash(long n)
{
  if(dp.find(n) != dp.end()) return dp[n];
  int c = 1;
  long norg = n;
  while(n!=1)
  {
    n = f(n);
    if(dp.find(n) != dp.end())
    {
      dp[norg] = c+dp[n];
      return dp[norg];
    }
    c+=1;
    dp[norg] = c;
  }
  return c;
}

long
chainD(long n)
{
  long c = 1;
  while(n!=1)
  {
    n = f(n);
    c += 1;
  }
  return c;
}

int
main()
{
  int max = 1;
  int maxchain = 1;
  for(long long i=1LL; i<1000000LL; i++)
  {
    int nchain = chain(i);
    if(maxchain < nchain)
    {
      maxchain = nchain;
      max = i;
    }
  }
  printf("%d\n", max);
}
