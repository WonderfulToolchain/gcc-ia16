/* { dg-do assemble } */
/* { dg-options "-std=gnu11 --save-temps" } */

/* Test that right arithmetic shifts of a 32-bit integer by 1, 2, and 3 bits,
   and shifts of a 64-bit integer by 1 bit, are done with the help of the
   `sarw' and `rcrw' instructions --- rather than using the GCC middle-end's
   rather inefficient synthesis.

   This isue was reported by Bart Oldeman --- see https://github.com/tkchia/
   gcc-ia16/issues/34 .  */

long sar1 (long x)
{
  return x >> 1;
}

long sar2 (long x)
{
  return x >> 2;
}

long sar3 (long x)
{
  return x >> 3;
}

long long sarl1ll (long long x)
{
  return x >> 1;
}

/* { dg-final { scan-assembler-times "sarw" 7 } } */
/* { dg-final { scan-assembler-times "rcrw" 9 } } */
