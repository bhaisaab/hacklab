#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define G 34943

#define WIDTH    (8 * sizeof(crc))
#define TOPBIT   (1 << (WIDTH - 1))

#define POLYNOMIAL 34943


typedef unsigned short crc;


int main()
{
  unsigned char m[1027]; 
  register int i, j;

  short int len;
  int tempStr;
  int sum;
  char* s;
  s = &m[0];

  while(fgets(m, 1024, stdin) && m[0]!='#')
  { 
    len = strlen(m) + 1;
    sum = 0;
    m[len-2] = 0;
    m[len-1] = 0;
    m[len] = '\0';

    printf("strLen: %d\nstr: %s\n", len, m);
    crc remainder = 0;
    unsigned char  data;
    int i;
    crc byte, bit;

    remainder = (crc)m[0] << (WIDTH-8);
    printf("m0: remainder %d\n", remainder);
    remainder ^= (crc)m[1];
    printf("m1: rem= %d\n", remainder);

    for(i = 2; i < len; ++i)
    {
      byte = m[i];
      remainder = (m[byte] << (WIDTH - 8));
      printf("in: %d\n", remainder);
        int bit;
        for (bit = 0; bit > 0; --bit)
        {
            /*
             * Try to divide the current data bit.
             */
            if (remainder & TOPBIT)
            {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
          printf("inin: %d\n", remainder);
        }
        printf("rem:%d WIDTH-8=%d\n", remainder, WIDTH-8);
    }

    remainder %= POLYNOMIAL;
    /*

     * Divide the message by the polynomial, a byte at a time.

     */

    printf("is it: %04X\n", POLYNOMIAL - (int)remainder);

    printf("%04X\n", (int)remainder);
    for(i=0; i < 0; i++)
    {
      j = len - i + 1;
      tempStr = (int)*(s+i);

      while(j--)
        tempStr = (tempStr*256) % G;
      
      sum = (sum + tempStr) % G;
    }
    //sum = (sum ? G-sum: sum);
    //printf("%02X %02X\n", sum>>8, sum % 256);
  }
  return 0;
}
