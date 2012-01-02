#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define G 34943

int main()
{
  char m[1025];
  register int i, j;

  short int len;
  int tempStr;
  int sum;
  char* s;
  s = &m[0];

  while(fgets(m, 1024, stdin) && m[0]!='#')
  { 
    len = strlen(m) - 1;
    sum = 0;

    for(i=0; i < len; i++)
    {
      j = len - i + 1;
      tempStr = (int)*(s+i);

      while(j--)
        tempStr = (tempStr*256) % G;
      
      sum = (sum + tempStr) % G;
    }
    sum = (sum ? G-sum: sum);
    printf("%02X %02X\n", sum>>8, sum % 256);
  }
  return 0;
}
