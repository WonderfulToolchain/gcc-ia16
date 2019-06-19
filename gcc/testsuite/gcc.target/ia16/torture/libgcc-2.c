/* { dg-do run } */
/* { dg-options "-std=gnu11 --save-temps" } */

/* Test whether the assembly language versions of the __divsi3 and __modsi3
   helper functions in libgcc work correctly.

   The code is adapted from the i386 test case gcc/testsuite/gcc.target/i386/
   divmod-1.c .  */

extern void abort (void);

void
__attribute__((noinline))
test (long x, long y, long q, long r)
{
  if ((x / y) != q || (x % y) != r)
    abort ();
}

int
main ()
{
  test (7L, 6L, 1L, 1L);
  test (-7L, -6L, 1L, -1L);
  test (-7L, 6L, -1L, -1L);
  test (7L, -6L, -1L, 1L);
  test (17L, 3L, 5L, 2L);
  test (-17L, -3L, 5L, -2L);
  test (-17L, 3L, -5L, -2L);
  test (17L, -3L, -5L, 2L);
  test (65535L, 65534L, 1L, 1L);
  test (-65535L, -65534L, 1L, -1L);
  test (-65535L, 65534L, -1L, -1L);
  test (65535L, -65534L, -1L, 1L);
  test (65536L, 65534L, 1L, 2L);
  test (-65536L, -65534L, 1L, -2L);
  test (-65536L, 65534L, -1L, -2L);
  test (65536L, -65534L, -1L, 2L);
  test (65536L, 65536L, 1L, 0L);
  test (-65536L, -65536L, 1L, 0L);
  test (-65536L, 65536L, -1L, 0L);
  test (65536L, -65536L, -1L, 0L);
  test (65534L, 65536L, 0L, 65534L);
  test (-65534L, -65536L, 0L, -65534L);
  test (-65534L, 65536L, 0L, -65534L);
  test (65534L, -65536L, 0L, 65534L);
  test (65534L, 65535L, 0L, 65534L);
  test (-65534L, -65535L, 0L, -65534L);
  test (-65534L, 65535L, 0L, -65534L);
  test (65534L, -65535L, 0L, 65534L);
  test (65534L, 1L, 65534L, 0L);
  test (-65534L, -1L, 65534L, 0L);
  test (-65534L, 1L, -65534L, 0L);
  test (65534L, -1L, -65534L, 0L);
  test (65535L, 2L, 32767L, 1L);
  test (-65535L, -2L, 32767L, -1L);
  test (-65535L, 2L, -32767L, -1L);
  test (65535L, -2L, -32767L, 1L);
  test (1L, 65536L, 0L, 1L);
  test (-1L, -65536L, 0L, -1L);
  test (-1L, 65536L, 0L, -1L);
  test (1L, -65536L, 0L, 1L);
  return 0;
}
