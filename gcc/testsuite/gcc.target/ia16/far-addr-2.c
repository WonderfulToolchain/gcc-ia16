/* { dg-do run } */
/* { dg-options "-O3 --save-temps" } */

/* What happens when we add a displacement to a long integer _before_
   converting it to a far pointer?  Make sure that the compiler does not try
   to wrongly "optimize" this by placing the displacement in the final IA-16
   address expression. */

int printf (const char *, ...);
void abort (void);

static inline unsigned long
read_displaced (unsigned long addr, unsigned disp)
{
  unsigned long addr2;

  __asm ("" : "=k" (addr2) : "0" (addr));
  return *(volatile unsigned long __far *) (addr2 + disp);
}

static void
test (const char *wx_name, unsigned long wx, unsigned long w0)
{
  if (wx == w0)
    printf ("%s == w0\n", wx_name);
  else
    {
      printf ("%s != w0 {%#lx != %#lx}\n", wx_name, wx, w0);
      abort ();
    }
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
  test ("w1", w1, w0);

  /* Read longword at (__far *) (0x78001 + 0x7fff), which should also be the
     same as 0x80000. */
  w2 = read_displaced (0x78001ul, 0x7fffu);
  test ("w2", w2, w0);

  /* And so on... */
  w3 = read_displaced (0x70001ul, 0xffffu);
  test ("w3", w3, w0);

  w4 = read_displaced (0x7ff80ul, 0x80u);
  test ("w4", w4, w0);

  w5 = read_displaced (0x7ff81ul, 0x7fu);
  test ("w5", w5, w0);

  w6 = read_displaced (0x7ff01ul, 0xffu);
  test ("w6", w6, w0);

  w7 = read_displaced (0x7fffful, 1u);
  test ("w7", w7, w0);

  return 0;
}
