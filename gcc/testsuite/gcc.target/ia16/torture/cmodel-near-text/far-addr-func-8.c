/* { dg-options "-std=gnu11 -mno-far-function-if-far-return-type --save-temps" } */
/* { dg-do assemble } */

/* Test that we do _not_ consider a function to be far, even if the return
   type is far, if the `-mfar-function-if-far-return-type' option is
   explicitly turned off.  */

extern int foo (long) __far __attribute__ ((near_section));

int __far
bar (long x)
{
  return foo (x) + 1;
}

/* { dg-final { scan-assembler "ret" } } */
/* { dg-final { scan-assembler-not "lret" } } */
/* { dg-final { scan-assembler "pushw\\t%cs" } } */
