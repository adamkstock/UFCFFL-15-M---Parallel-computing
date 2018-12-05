#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


#define NUM_THREADS 4

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

  char truekey [17] = "#####999999#####";
  char originaltxt [17] = "thisisatestxxxxx";
  char encryptedtxt [17+cbs];

  int ret;
  double timer;

  encrypt (originaltxt, strlen (originaltxt), truekey, iv,  encryptedtxt);

  clock_t time1, time2;

  time1 = clock();

  omp_set_num_threads(NUM_THREADS);


    int i1, i2, i3, i4, i5;


    char starttestkey [17] = "#####000000#####";

    for (i1 = 0;i1 <= 9; i1++)
    {
      starttestkey[5] = i1 + '0' ;
      for (i2 = 0;i2 <= 9; i2++)
      {
        starttestkey[6] = i2 + '0' ;
        for (i3 = 0;i3 <= 9; i3++)
        {
          starttestkey[7] = i3 + '0' ;
          for (i4 = 0;i4 <= 9; i4++)
          {
            starttestkey[8] = i4 + '0' ;
            for (i5 = 0;i5 <= 9; i5++)
            {
              starttestkey[9] = i5 + '0' ;
              #pragma omp parallel
              {
                int i6;
                int idstart = 3 * omp_get_thread_num();
                char testkey [17] ;
                strcpy (testkey, starttestkey);
                char work [17+cbs];
                for (i6 = idstart;i6 <= 9; i6++)
                {
                  testkey[10] = i6 + '0' ;

                  encrypt (originaltxt, strlen ((char*)originaltxt), testkey, iv,  work);

                  ret = strncmp(work, encryptedtxt, 16);

                  if (ret == 0)
                  {
                    time2 = clock();
                    timer = time2 - time1;
                    int id = omp_get_thread_num();
                    printf ("[---------------------------------]\n\n");
                    printf ("Match found\n\n");
                    printf("Time %f\n", (timer / CLOCKS_PER_SEC));
                    printf("key = %s\n", testkey);
                    printf("thread = %d\n", id);
                    printf ("[---------------------------------]\n\n");
                  }
                }
              }
            }
          }
        }
      }
    }

  return 0;
}
