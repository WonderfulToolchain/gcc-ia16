/* { dg-do run } */
/* { dg-xfail-if "" *-*-* } */
/* { dg-xfail-run-if "" *-*-* } */
/* { dg-options "-O3 -fno-inline --save-temps" } */

/* FAIL: Far pointers to non-volatile things.  For the same read-only memory
   area, using non-volatile pointers should give the same results as using
   volatile pointers.

   Currently this crashes the compiler.  */

int printf (const char *, ...);

unsigned long
hash1 (void)
{
  unsigned __far *p = (unsigned __far *) 0xf0000000ul;
  unsigned i;
  unsigned long h = 0;
  for (i = 0; i < 2000; ++i)
    h = 5 * h ^ *p++;
  return h;
}

unsigned long
hash2 (void)
{
  volatile unsigned __far *p = (volatile unsigned __far *) 0xf0000000ul;
  unsigned i;
  unsigned long h = 0;
  for (i = 0; i < 2000; ++i)
    h = 5 * h ^ *p++;
  return h;
}

int
main (void)
{
  unsigned long h1 = hash1 (), h2 = hash2 ();
  printf ("%#lx %#lx\n", h1, h2);
  return h1 == h2 ? 0 : 1;
}
