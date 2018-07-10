/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do run } */

/* Test that we can use __builtin_ia16_FP_OFF (.) in a static initializer,
   on a pointer to an externally visible function defined in the same
   translation unit.

   This test case is partly taken from the FreeDOS kernel code (in
   kernel/main.c).  -- tkchia */

#ifndef __BUILTIN_IA16_FP_OFF
# error
#endif

__attribute__ ((stdcall, far_section)) void
int0_handler (void) __far
{
}

struct vec {
  unsigned char intno;
  unsigned handleroff __attribute__ ((packed));
} vectors[] = { 0, __builtin_ia16_FP_OFF (int0_handler) };

void abort (void);

int
main (void)
{
  if ((void *) vectors[0].handleroff != (void *) int0_handler)
    abort ();

  return 0;
}

/* { dg-final { scan-assembler "\.hword\[ \\t\]int0_handler" } } */
