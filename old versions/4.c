#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  /* Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}


int main (void)
{

  unsigned char *iv = (unsigned char *)"0123456789012345";

  int cbs = EVP_CIPHER_block_size(EVP_aes_128_cbc());

  char truekey [17] = "#####123456#####";
  char originaltxt [17] = "thisisatestxxxxx";
  char encryptedtxt [17+cbs];
  char work [17+cbs];
  char testkey [17] = "#####xxxxxx#####";

  int i1, i2, i3, i4, i5, i6;
  int ret;
  double timer;

  encrypt (originaltxt, strlen (originaltxt), truekey, iv,  encryptedtxt);

  clock_t time1, time2;

  time1 = clock();

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

              //printf("%s\n", testkey);

              //encrypt (originaltxt, testkey, work)
              encrypt (originaltxt, strlen ((char*)originaltxt), testkey, iv,  work);

              ret = strcmp(work, encryptedtxt);

              if (ret == 0)
              {
                printf ("Match found\n\n");
                time2 = clock();
                timer = time2 - time1;
                printf("Time %f\n", (timer / CLOCKS_PER_SEC));
                return 0;
              }
              // if (work == encryptedtxt)
              // {
              //   printf("Match");
              //   return 0;
              // }
            }
          }
        }
      }
    }
  }

  return 0;
}
