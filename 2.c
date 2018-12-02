#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char truekey [16] = "#####123456#####";
char originaltxt [16] = "thisisatestxxxxx";
char encryptedtxt [16];
char work [16];
char testkey [16] = "#####xxxxxx#####";

int main (void)
{
  // encrypt (originaltxt, truekey, encryptedtxt)

  int i1, i2, i3, i4, i5, i6;
  int ret;

  for (i1 = 0;i1 <= 9; i1++)
  {
    testkey[5] = i1 + '0' ;
    for (i2 = 0;i2 <= 9; i2++)
    {
      testkey[6] = i2 + '0' ;
      for (i3 = 0;i3 <= 9; i3++)
      {
        testkey[7] = i3 + '0' ;
        for (i4 = 0;i4 <= 9; i4++)
        {
          testkey[8] = i4 + '0' ;
          for (i5 = 0;i5 <= 9; i5++)
          {
            testkey[9] = i5 + '0' ;
            for (i6 = 0;i6 <= 9; i6++)
            {
              testkey[10] = i6 + '0' ;

              printf("%s\n", testkey);

              //encrypt (originaltxt, testkey, work)

              //ret = strcmp(work, encryptedtxt)

              //if (ret == 0)
              //{
              //  printf ("Match found");
              //}
            }
          }
        }
      }
    }
  }
}
