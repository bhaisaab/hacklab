#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
#include <list>
using namespace std;

int compare (const void * a, const void * b)
{
  return ( *(int*)b - *(int*)a );
}

int main()
{
  int n;
  int coins[100];
  int ans; int sum = 0;
  scanf("%d", &n);
  for(int i=0; i<n; i++) {
    scanf("%d", &coins[i]); sum+=coins[i];
  }
  qsort(coins, n, sizeof(int), compare);
  int mysum = 0;
  for(int i=0;sum >= mysum; i++)
  {
    mysum+=coins[i];
    sum-=coins[i];
    ans = i+1;
  }
  printf("%d", ans);
  return 0;
}
