/* { dg-do run } */
/* { dg-options "-O3 -fno-inline --save-temps" } */

/* Test that the "e" register constraint works properly.  */

void abort (void);

int
f (void)
{
  int x;
  __asm(".ifnc \"%%es\", \"%0\"; "
	".err; "
	".endif"
    : "=e" (x) : "0" (0xbe3f));
  return x;
}

int
main (void)
{
  if (f () != 0xbe3f)
    abort ();
  return 0;
}
