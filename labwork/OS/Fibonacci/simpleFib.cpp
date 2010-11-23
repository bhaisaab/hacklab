#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define MAX 500

using namespace std;
unsigned long long int results[MAX];

int main()
{
	int total;
  int x=0ll, y=1ll, z=0ll;
  freopen("/home/rohit/input", "r", stdin);
  scanf("%d", &total);
  
  if(total < 2)
    return 0;
  for(int i=0;i<total;i++)
  {
    results[i] = z;
    z=x+y;
    x=y;  
    y=z;
  }

  printf("Fibonacci series:\n");
  for(int i=0;i<total;i++)
	{
		printf("%llu\t", results[i]);
	}
	return 0;
}
