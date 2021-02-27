/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do run } */

/* Test whether calls and returns for interrupt functions work correctly,
   and push and pop the correct number of shortwords each time. */

extern void abort (void);

unsigned thang = 0x89b2u;

static void __far __attribute__ ((interrupt, noinline))
isr (void)
{
  while (thang != 0x89b2u);
}

int
main (void)
{
  unsigned i;

  for (i = 0; i < 0xc000; ++i)
    {
      isr ();
      if (thang != 0x89b2u)
	abort ();
    }

  return 0;
}
