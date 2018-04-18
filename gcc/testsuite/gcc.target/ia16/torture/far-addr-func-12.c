/* { dg-options "-mcmodel=small -std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that a call from a module to a far function (sans `__attribute__
   ((near_section))') outside the module is done with an `lcall' or `ljmp'
   instruction, if the call can be made a sibcall.

   (The code requires the small memory model, as the `lcall' or `ljmp' will
   very likely need a segment relocation.)  */

extern int foo (long) __far;

int
bar (long x)
{
  return foo (x * x);
}

/* { dg-final { scan-assembler "l(call|jmp)\[ \\t\].*,\[ \\t\]\\\$foo" } } */
