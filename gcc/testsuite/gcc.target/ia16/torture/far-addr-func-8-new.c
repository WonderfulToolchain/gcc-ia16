/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that we _do_ consider a function to be far, if the return type is far,
   under the default configuration of -mfar-function-if-far-return-type.  */

extern int __far foo (long) __attribute__ ((near_section));

int __far
bar (long x)
{
  return foo (x) + 1;
}

/* { dg-final { scan-assembler-not "\[ \\t\]ret" } } */
/* { dg-final { scan-assembler "lret" } } */
/* { dg-final { scan-assembler "pushw\\t%cs" } } */
