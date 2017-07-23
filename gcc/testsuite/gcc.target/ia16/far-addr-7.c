/* { dg-do run } */
/* { dg-options "-O3 -fno-inline --save-temps" } */

/* Using a far pointer to loop through an area of (emulated) BIOS ROM.  */

int printf (const char *, ...);

unsigned long
hash (void)
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
  printf ("%#lx\n", hash ());
  return 0;
}
