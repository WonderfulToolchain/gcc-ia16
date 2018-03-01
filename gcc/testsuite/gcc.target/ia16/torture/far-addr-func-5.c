/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that we can define far functions using the postfix __far syntax.  */

int
one (void) __far
{
  return 1;
}

/* { dg-final { scan-assembler "lret" } } */
