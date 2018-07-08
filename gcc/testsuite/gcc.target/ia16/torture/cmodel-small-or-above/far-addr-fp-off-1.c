/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that __builtin_ia16_FP_OFF (.) works in static initializers.

   This test case is partly taken from the FreeDOS kernel code (in
   kernel/main.c).  -- tkchia */

#ifndef __BUILTIN_IA16_FP_OFF
# error
#endif

void int0_handler (void) __far __attribute__ ((stdcall));

struct vec {
  unsigned char intno;
  unsigned handleroff __attribute__ ((packed));
} vectors[] = { 0, __builtin_ia16_FP_OFF (int0_handler) };

/* { dg-final { scan-assembler "\.hword\[ \\t\]int0_handler" } } */
