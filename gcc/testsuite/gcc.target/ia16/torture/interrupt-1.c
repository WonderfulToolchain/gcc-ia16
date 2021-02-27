/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-additional-sources "support/interrupt-isr.S" } */
/* { dg-do run } */

/* Test whether calls and returns for interrupt functions work correctly,
   and push and pop the correct number of shortwords each time. */

#ifdef __IA16_CMODEL_TINY__
extern void __far __attribute__ ((interrupt, near_section)) isr (void);
#else
extern void __far __interrupt isr (void);
#endif
extern void abort (void);

unsigned thang = 0x89b2u;

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
