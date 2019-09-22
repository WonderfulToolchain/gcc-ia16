/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that a __far immediately after an old-style function declarator in
   a function definition is _not_ interpreted as saying that the function
   itself is far.  */

void
swap (x, y)
  __far int *x, *y;
{
  int t = *x;
  *x = *y;
  *y = t;
}

/* { dg-final { scan-assembler "ret" } } */
/* { dg-final { scan-assembler-not "lret" } } */
