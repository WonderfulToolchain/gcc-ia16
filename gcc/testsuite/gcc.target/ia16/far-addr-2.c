/* { dg-do run } */
/* { dg-options "-O3 --save-temps" } */

/* What happens when we add a displacement to a long integer _before_
   converting it to a far pointer?  Make sure that the compiler does not try
   to wrongly "optimize" this by placing the displacement in the final IA-16
   address expression. */

int puts (const char *);
void abort (void);

static inline unsigned long
read_displaced (unsigned long addr, unsigned disp)
{
  unsigned long addr2;

  __asm ("" : "=k" (addr2) : "0" (addr));
  return *(volatile unsigned long __far *) (addr2 + disp);
}

int
main (void)
{
  unsigned long w0, w1, w2, w3, w4, w5, w6, w7;

  /* Read longword at 0x0008:0x0000. */
  w0 = *(volatile unsigned long __far *) 0x80000;

  /* Read longword at (__far *) (0x78000 + 0x8000), which should be the same
     as 0x80000, since we are doing the addition as integers first. */
  w1 = read_displaced (0x78000ul, 0x8000u);
  if (w1 != w0)
    abort ();
  puts ("w1 == w0");

  /* Read longword at (__far *) (0x78001 + 0x7fff), which should also be the
     same as 0x80000. */
  w2 = read_displaced (0x78001ul, 0x7fffu);
  if (w2 != w0)
    abort ();
  puts ("w2 == w0");

  /* And so on... */
  w3 = read_displaced (0x70001ul, 0xffffu);
  if (w3 != w0)
    abort ();
  puts ("w3 == w0");

  w4 = read_displaced (0x7ff80ul, 0x80u);
  if (w4 != w0)
    abort ();
  puts ("w4 == w0");

  w5 = read_displaced (0x7ff81ul, 0x7fu);
  if (w5 != w0)
    abort ();
  puts ("w5 == w0");

  w6 = read_displaced (0x7ff01ul, 0xffu);
  if (w6 != w0)
    abort ();
  puts ("w6 == w0");

  w7 = read_displaced (0x7fffful, 1u);
  if (w7 != w0)
    abort ();
  puts ("w7 == w0");

  return 0;
}
