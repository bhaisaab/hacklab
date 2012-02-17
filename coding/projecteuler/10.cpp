#include <stdio.h>
#include <math.h>

int main()
{
  long unsigned int limit = 2000000;
  long sievebound = (limit-1)/2;
  bool sieve[1000000]; //sievebound+1 size, 0 is dummy
  int crosslimit = (floor(sqrt(limit)) - 1) /2;

  sieve[0] = false;
  for(int i=1; i <= sievebound; i++)
    sieve[i] = true;

  for(int i=1; i <= crosslimit; i++)
  {
    if(sieve[i])
    {
      int j = 2*i*(i+1); //got prime
      while(j <= sievebound)
      {
        sieve[j] = false;
        j += (2*i+1);
      }
    }
  }
  long long unsigned int sum = 2LLU;
  for(int i = 1; i <= sievebound; i++)
    if(sieve[i])
      sum = sum + (2*i+1);

  printf("%llu\n", sum);
  return 0;
}
