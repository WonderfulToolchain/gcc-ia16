/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-additional-sources "support/interrupt-isr.S" } */
/* { dg-do run } */

/* Test whether calls and returns for interrupt functions work correctly,
   and push and pop the correct number of shortwords each time, even when
   the calls go through function pointers.  */

extern void abort (void);

#ifdef __IA16_CMODEL_TINY__
void __far __attribute__ ((interrupt, near_section)) isr (void),
						     (*pisr1) (void);
#else
void __far __interrupt isr (void), (*pisr1) (void);
#endif
unsigned thang = 0x89b2u;

int
main (void)
{
#ifdef __IA16_CMODEL_TINY__
  void __far __attribute__ ((interrupt, near_section))
  (* volatile pisr2) (void);
#else
  void __far __interrupt (* volatile pisr2) (void);
#endif
  unsigned i;

  pisr1 = isr;
  pisr2 = isr;
  for (i = 0; i < 0xc000; ++i)
    {
      pisr1 ();
      pisr2 ();
      if (thang != 0x89b2u)
	abort ();
    }

  return 0;
}
