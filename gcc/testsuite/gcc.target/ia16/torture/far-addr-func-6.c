/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that we can define a function which is far _and_ stdcall.  */

__attribute__ ((stdcall)) int
add_one (long x) __far
{
  return x + 1;
}

/* { dg-final { scan-assembler "lret\[ \\t\]\\\$4" } } */
