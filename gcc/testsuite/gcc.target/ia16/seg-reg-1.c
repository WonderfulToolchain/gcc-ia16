/* { dg-do run } */
/* { dg-options "-O3 -fno-inline --save-temps" } */

/* Test that the "Q" register constraint works properly.  */

void abort (void);

unsigned
f (void)
{
  unsigned x;
  __asm(".ifnc \"%%ds\", \"%0\"; "
	".ifnc \"%%es\", \"%0\"; "
	".err; "
	".endif; "
	".endif"
    : "=Q" (x) : "0" (0x1337));
  return x;
}

int
main (void)
{
  if (f () != 0x1337)
    abort ();
  return 0;
}
