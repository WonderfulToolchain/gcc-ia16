/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that we can use __builtin_ia16_FP_OFF (.) in a static initializer,
   on a pointer to an external function.

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

/* { dg-final { scan-assembler "\.hword\[ \\t\]__ia16_alias" { target { ! lto } } } } */
/* { dg-final { scan-assembler "\.(weakref|set)\[ \\t\]__ia16_alias.*,int0_handler" { target { ! lto } } } } */
