#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
  int n;
  scanf("%d\n", &n);
  char buf[2*n];
  fgets(buf, 2*n+1, stdin);
  int num[2*n];
  for(int i=0; i<2*n; i++)
    num[i] = buf[i]-48;

  sort(num, num+n);
  sort(num+n, num+2*n);

  bool subarr1=true, subarr2=true;
  for(int i=0; i<n; i++)
  {
    if(num[i] >= num[i+n]) subarr1 = false;
    if(num[i] <= num[i+n]) subarr2 = false;
  }

  if(subarr1 || subarr2) printf("YES");
  else printf("NO");
  return 0;
}
