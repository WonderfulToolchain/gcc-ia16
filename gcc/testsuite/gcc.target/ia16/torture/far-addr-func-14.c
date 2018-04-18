/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that a call from a module to a far function with `__attribute__
   ((near_section))' is done with a near `call' or `jmp' instruction, if the
   call can be made a sibcall.  */

extern int foo (long) __far __attribute__ ((near_section));

int
bar (long x)
{
  return foo (x * x);
}

/* { dg-final { scan-assembler-not "l(call|jmp)\[ \\t\]" } } */
/* { dg-final { scan-assembler "(call|jmp)\[ \\t\]foo" } } */
