/* { dg-do assemble } */
/* { dg-options "--std=gnu11 --save-temps" } */

/* Test that, when a `far_section' function calls a `near_section' function,
   the resulting call instruction is a far call.  */

unsigned __far foo (unsigned) __attribute__ ((near_section));

__attribute__ ((far_section)) unsigned __far
bar (unsigned x)
{
  return foo (x) + 1;
}

/* { dg-final { scan-assembler "lcall\[ \\t\].*,\[ \\t\]\\\$foo" } } */
