/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/*
 * Test that we can cast a stack address to a far pointer without crashing
 * the compiler.  -- tkchia
 */

void abort (void);

int
foo (int *p)
{
  return *p + 10;
}

int
bar (int __far *p)
{
  return *p + 20;
}

int
main (void)
{
  auto int x = 1;
  if (foo (&x) != 11)
    abort ();
  if (bar (&x) != 21)
    abort ();
  return 0;
}
