/* { dg-do compile } */
/* { dg-options "-O3 -fno-inline --save-temps" } */
/* { dg-xfail-if "" *-*-* }

/* FAIL: Far pointers to non-volatile things.  They cause the compiler to
   crash (and they should not).  */

unsigned
hash (void)
{
  unsigned __far *p = (unsigned __far *) 0xb8000000ul;
  unsigned i, h = 0;
  for (i = 0; i < 2000; ++i)
    h = 5 * h ^ *p++;
  return h;
}
