/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do run } */

/* Test that we can use __builtin_ia16_FP_OFF (.) in a static initializer,
   on a pointer to an externally visible or locally visible variable.  */

#ifndef __BUILTIN_IA16_FP_OFF
# error
#endif

int __far var1;
static int __far var2;

unsigned var1_off = __builtin_ia16_FP_OFF (&var1);
unsigned var2_off = __builtin_ia16_FP_OFF (&var2);

void abort (void);

int
main (void)
{
  if ((void *) var1_off != (void *) &var1)
    abort ();

  if ((void *) var2_off != (void *) &var2)
    abort ();

  return 0;
}
