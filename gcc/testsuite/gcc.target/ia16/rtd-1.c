/* { dg-do run } */
/* { dg-options "-mrtd -Os --save-temps" } */

/* Test whether the `-mrtd' switch works correctly and links with the correct
   libgcc multilib.  This test should not require newlib to also be compiled
   with `-mrtd'.  */

extern void abort (void);

volatile unsigned long long quotient = 0x55bde67343803983ull,
			    divisor = 0x1670107447a23170ull;

unsigned
inc (unsigned x)
{
  return x + 1;
}

int main (int argc, char **argv, ...)
{
  unsigned i;

  /* If this code is linked against the wrong libgcc, this loop will
     eventually cause a stack overflow and corrupt the data area.  */
  for (i = 0; i < 10000; ++i)
    {
      unsigned long long mod = quotient % divisor;
      if (mod != 0x126db5166c99a533ull)
	abort ();
    }

  return 0;
}

/* inc (.) should pop one shortword: */
/* { dg-final { scan-assembler "ret\[ \\t\]\\\$2" } } */

/* main (...) should _not_ pop two shortwords: */
/* { dg-final { scan-assembler-not "ret\[ \\t\]\\\$4" } } */

/* main (...) should not adjust the stack after calling __umoddi3: */
/* { dg-final { scan-assembler-not "addw\[ \\t\]\\$.*,\[ \\t\]%sp" } } */
