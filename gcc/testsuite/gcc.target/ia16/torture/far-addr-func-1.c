/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that a call to a function in __far space is done with an `lcall'.  */

typedef int func_t (long);
typedef func_t __far far_func_t;

int
bar (far_func_t *foo, long x)
{
  return foo (x);
}

/* { dg-final { scan-assembler "lcall\[ \\t\].*\\(%bp\\)" } } */
