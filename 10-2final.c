#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <stdbool.h>
#include <mpi.h>

#define NUM_THREADS 2

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


int main (int argc, char* argv[])
{

  unsigned char *iv = (unsigned char *)"0123456789012345";

  int cbs = EVP_CIPHER_block_size(EVP_aes_128_cbc());

  char truekey [17] = "#####747065#####";
  char originaltxt [17] = "thisisatestxxxxx";
  char encryptedtxt [17+cbs];

  int ret;
  bool hit = false;
  double timer;

  encrypt (originaltxt, strlen (originaltxt), truekey, iv,  encryptedtxt);//initial encryption here 

  double time1, time2;

  time1 = omp_get_wtime();//timer started here 

  MPI_Init (&argc, &argv);      /* starts MPI */

  int threadno;
  MPI_Comm_rank (MPI_COMM_WORLD, &threadno);        /* get current process id */

    int i1, i2, i3, i4, i5, i6;
    char testkey [17] = "#####000000#####";
    char work [17+cbs];
    int idstart = 5 * threadno;
    for (i1 = idstart;i1 <= idstart + 4; i1++)
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

                encrypt (originaltxt, strlen ((char*)originaltxt), testkey, iv,  work);//second encryption here for comparison 

                ret = strncmp(work, encryptedtxt, 16);

                if (ret == 0)
                {
                  if (hit == false)
                  {
                    hit = true ;
                    time2 = omp_get_wtime();//timer stopped here 
                    timer = (double)(time2 - time1);
                    printf ("[---------------------------------]\n\n");
                    printf ("Match found\n\n");
                    printf("Time %f\n", timer);
                    printf("key = %s\n", testkey);
                    printf("thread = %d\n", threadno);
                    printf ("[---------------------------------]\n\n");
                  }
                }
              }
            }
          }
        }
      }
    }

    printf("Bye from thread %d\n", threadno);

    MPI_Finalize();

  return 0;
}
