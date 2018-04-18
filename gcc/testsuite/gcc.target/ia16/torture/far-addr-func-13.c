/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that a call from a module to a far function with `__attribute__
   ((near_section))' is not done with an `lcall' instruction.  */

extern int foo (long) __far __attribute__ ((near_section));

int
bar (long x)
{
  return foo (x) + 1;
}

/* { dg-final { scan-assembler-not "lcall\[ \\t\]" } } */
/* { dg-final { scan-assembler "call\[ \\t\]foo" } } */
