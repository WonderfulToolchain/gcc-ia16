/* { dg-do run } */
/* { dg-options "-O3 -fno-inline --save-temps" } */

/* Far pointers to non-volatile things.  For the same read-only memory area,
   using pointers to non-`volatile' should give the same results as using
   pointers to `volatile'.

   We also include further tests where the _pointers_ themselves are made
   volatile (not necessarily the things pointed to).  */

int printf (const char *, ...);

unsigned long
hash1 (void)
{
  unsigned __far *p = (unsigned __far *) 0xf0000000ul;
  unsigned i;
  unsigned long h = 0;
  for (i = 0; i < 0x8000u; ++i)
    h = 5 * h ^ *p++;
  return h;
}

unsigned long
hash2 (void)
{
  volatile unsigned __far *p = (volatile unsigned __far *) 0xf0000000ul;
  unsigned i;
  unsigned long h = 0;
  for (i = 0; i < 0x8000u; ++i)
    h = 5 * h ^ *p++;
  return h;
}

unsigned long
hash3 (void)
{
  unsigned __far * volatile p = (unsigned __far *) 0xf0000000ul;
  unsigned i;
  unsigned long h = 0;
  for (i = 0; i < 0x8000u; ++i)
    h = 5 * h ^ *p++;
  return h;
}

unsigned long
hash4 (void)
{
  volatile unsigned __far * volatile p =
    (volatile unsigned __far *) 0xf0000000ul;
  unsigned i;
  unsigned long h = 0;
  for (i = 0; i < 0x8000u; ++i)
    h = 5 * h ^ *p++;
  return h;
}

int
main (void)
{
  unsigned long h1 = hash1 (), h2 = hash2 (), h3 = hash3 (), h4 = hash4 ();
  printf ("%#lx %#lx %#lx %#lx\n", h1, h2, h3, h4);
  return h1 == h2 && h1 == h3 && h1 == h4 ? 0 : 1;
}
