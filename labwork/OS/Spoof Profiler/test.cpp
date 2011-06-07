#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

const int N=10;              // # of elements in array

int main() {
  cout << "Start of tests" << endl;
  int *p1 = new int(1);      // use to cause leak
  int *p2 = new int[N];      // allocate an int array
  int *p3 = new int(2);      // used to test wrong delete
  char *cp = 0;              // cp is null pointer
  char ca[3];                // unintialized array
  cout << "Test 1: off by one" << endl;
  for (int i=1; i<N+1; i++)  // one-off in loop
    p2[i] = i;               // err - initialize element p[N]
  cout << "Test 2: access freed storage" << endl;
  delete p1;
  *p1 = 3;                   // err - accessing freed storage
  cout << "Test 3: using uninitialized storage" << endl;
  if (p2[0]) cout << "Junk" << endl;// err - used uninit data
  cout << "Test 4: delete array using scalar delete" << endl;
  delete p2;                 // err - delete array with scalar delete
  cout << "Test 5: array delete of scalar" << endl;
  delete [] p3;              // err - array delete of scalar
  cout << "Test 6: overlapping storage blocks" << endl;
  memcpy( ca, &ca[1],2 );    // err - overlapping storage blocks
  cout << "Test 7: system call using uninitialize data" << endl;
 // sleep( ca[0] );            // err - uninit data in system call
 // cout << "Test 8: assign to null pointer - seg faults" << endl;
 // *cp = 'a';                 // err - used null pointer (Seg fauilts)
  cout << "End of tests" << endl;
  return 0;
}
