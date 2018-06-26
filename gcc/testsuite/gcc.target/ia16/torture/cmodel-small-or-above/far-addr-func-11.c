/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that a call from a module to a far function (sans `__attribute__
   ((near_section))') outside the module is done with an `lcall'
   instruction.

   (The code requires the small memory model or above, as the `lcall' will
   very likely need a segment relocation.) */

extern int foo (long) __far;

int
bar (long x)
{
  return foo (x) + 1;
}

/* { dg-final { scan-assembler "lcall\[ \\t\].*,\[ \\t\]\\\$foo" } } */
