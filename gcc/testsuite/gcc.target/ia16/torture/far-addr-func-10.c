/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that far function calls work even with when the far function pointers
   hide out in weird places.  */

struct s
{
  double d;
  union
    {
      int (*fpf) (long) __far;
      int (*npf) (long);
    } u;
  int i;
};

int
foo (struct s * (*bar) (float), float baz, long qux)
{
  return bar (baz)->u.fpf (qux);
}

/* { dg-final { scan-assembler-times "lcall\[ \\t\]\\*" 1 } } */
