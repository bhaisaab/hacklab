//Find smallest non-negative integer not in a list
//O(log n)

int res = 0;

void algo(int* a, int start, int end)
{
 if (start > end) return;

 int mid = (start+end) /2;

 if (a[mid] == mid) // search right part
 {
   //res = mid+1;
   algo(a, mid+1,end);
 }
 else // search left
 {
   res = mid;
   algo(a, start, mid-1);
 }
}  

int binsearch(int*a, int val, int start, int end);

int main()
{
 int a[] = {0,1,2,3,4,5,6,7};
 int b[] = {0,1,5,6,7,8,9,11};
 int c[] = {0,2,3,4,5,6,7,10};
 int d[] = {0,1,2,6,18,20,22,28};
 int n = 8;
 //do binary search for 0, and pass the index to
 //int index = binsearch(a, 0, n);
 // if zero is not found, then zero is the answer
 res = a[n-1]+1;
 algo(a,0,n-1);
 printf("result is %d\n", res);  

 res = b[n-1]+1;
 algo(b,0,n-1);
 printf("result is %d\n", res);  

 res = c[n-1]+1;
 algo(c,0,n-1);
 printf("result is %d\n", res);  

 res = d[n-1]+1;
 algo(d,0,n-1);
 printf("result is %d\n", res);  
}


