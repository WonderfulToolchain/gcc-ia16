/* { dg-do run } */
/* { dg-options "-O3 -fno-inline --save-temps" } */

/* Using a far pointer to loop through an area of conventional memory.  */

int printf (const char *, ...);

unsigned
hash (void)
{
  volatile unsigned __far *p = (volatile unsigned __far *) 0xb8000000ul;
  unsigned i, h = 0;
  for (i = 0; i < 2000; ++i)
    h = 5 * h ^ *p++;
  return h;
}

int
main (void)
{
  printf ("%#x\n", hash ());
  return 0;
}
