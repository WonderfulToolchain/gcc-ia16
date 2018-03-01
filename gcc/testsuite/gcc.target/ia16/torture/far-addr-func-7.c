/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that we can define a function which is far _and_ cdecl.  */

__attribute__ ((cdecl)) int
add_one (long x) __far
{
  return x + 1;
}

/* { dg-final { scan-assembler "lret" } } */
/* { dg-final { scan-assembler-not "lret\[ \\t\]\\\$4" } } */
