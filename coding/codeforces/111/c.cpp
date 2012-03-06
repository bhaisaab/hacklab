#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  unsigned long long int n,k;
  long long int arr[100011];
  cin >> n;
  cin >> k;
  for(int i=0; i<n; i++)
    cin >> arr[i];
  sort(arr, arr+n);
  long long i=0, j, ct;
  while(i<n)
  {
    long long a = arr[i];
    j = i+1;
    while(j<n && arr[j] == arr[i]) j++;
    ct = j-i;
    if(k>ct*n)
    {
      k-=ct*n;
      i=j; //update counter
    }
    else
    {
      printf("%lld %lld", a, arr[(k-1)/ct]); break;
    }
  }
  return 0;
}
