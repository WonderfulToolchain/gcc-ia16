/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do run } */

/* Test whether the assembly language versions of the __udivsi3 and __umodsi3
   helper functions in libgcc work correctly, under various calling
   conventions.  */

extern void abort (void);

/* This code may fail in two ways:
     * If linked against the wrong libgcc, the main () loop will eventually
       cause a stack overflow and corrupt the data area.
     * If the division is done wrong, the loop will call abort ().  Here I
       test for a known issue reported by Gerd Grosse in the context of the
       FreeDOS kernel (https://sourceforge.net/p/freedos/bugs/106/).  */

volatile unsigned long quotient1 = 0xbdaf6f1bul, divisor1 = 0x083b9222ul,
		       quotient2 = 0xffff01fful, divisor2 = 0x010101fful;

int
main (void)
{
  unsigned i;

  for (i = 0; i < 10000; ++i)
    {
      unsigned long dividend, modulus;

      dividend = quotient1 / divisor1;
      if (dividend != 0x17ul)
	abort ();

      modulus = quotient1 % divisor1;
      if (modulus != 0x554e0dul)
	abort ();

      dividend = quotient2 / divisor2;
      if (dividend != 0xfeul)
	abort ();

      modulus = quotient2 % divisor2;
      if (modulus != 0xff06fdul)
	abort ();
    }

  return 0;
}
