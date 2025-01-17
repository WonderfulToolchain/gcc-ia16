/* { dg-do assemble } */
/* { dg-options "-std=gnu11 --save-temps" } */

/* Test that right logical shifts of a 32-bit integer by 1, 2, and 3 bits,
   and shifts of a 64-bit integer by 1 bit, are done with the help of the
   `shrw' and `rcrw' instructions --- rather than using the GCC middle-end's
   rather inefficient synthesis.

   This isue was reported by Bart Oldeman --- see https://github.com/tkchia/
   gcc-ia16/issues/34 .  */

unsigned long shr1 (unsigned long x)
{
  return x >> 1;
}

unsigned long shr2 (unsigned long x)
{
  return x >> 2;
}

unsigned long shr3 (unsigned long x)
{
  return x >> 3;
}

unsigned long long shrl1ll (unsigned long long x)
{
  return x >> 1;
}

/* { dg-final { scan-assembler-times "shrw" 7 } } */
/* { dg-final { scan-assembler-times "rcrw" 9 } } */
