/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that, under the default -mfar-function-if-far-return-type setting,
   a far function returning void declared using the classical syntax does
   not give a "function with qualified void return type called" warning.

   Reported by Bart Oldeman --- https://github.com/tkchia/gcc-ia16/issues/25 .
 */

extern void __far foo (void);

void
bar (void)
{
  foo ();	/* { dg-bogus "function with qualified void return type" } */
}
