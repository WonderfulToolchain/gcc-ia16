/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that we can use __builtin_ia16_FP_OFF (.) in a static initializer,
   on a pointer to an external variable.  */

#ifndef __BUILTIN_IA16_FP_OFF
# error
#endif

extern int __far var1;

unsigned var1_off = __builtin_ia16_FP_OFF (&var1);
