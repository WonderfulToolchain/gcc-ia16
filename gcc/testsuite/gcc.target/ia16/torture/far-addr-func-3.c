/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that the postfix __far syntax for declaring far functions works.  */

int
bar (int (*foo) (long) __far, long x)
{
  return foo (x);
}

/* { dg-final { scan-assembler "lcall\[ \\t\].*\\(%bp\\)" } } */
