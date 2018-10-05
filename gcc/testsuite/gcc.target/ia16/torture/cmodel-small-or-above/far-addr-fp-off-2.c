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
  __asm volatile ("# in int 0");
}

__attribute__ ((stdcall, far_section)) void
int6_handler (void) __far
{
  __asm volatile ("# in int 6");
}

__attribute__ ((stdcall, far_section)) void
int19_handler (void) __far
{
  __asm volatile ("# in int 19");
}

__attribute__ ((stdcall, far_section)) void
int20_handler (void) __far
{
  __asm volatile ("# in int 20");
}

__attribute__ ((stdcall, far_section)) void
int21_handler (void) __far
{
  __asm volatile ("# in int 21");
}

__attribute__ ((stdcall, far_section)) void
int24_handler (void) __far
{
  __asm volatile ("# in int 24");
}

__attribute__ ((stdcall, far_section)) void
int25_handler (void) __far
{
  __asm volatile ("# in int 25");
}

__attribute__ ((stdcall, far_section)) void
int26_handler (void) __far
{
  __asm volatile ("# in int 26");
}

__attribute__ ((stdcall, far_section)) void
int27_handler (void) __far
{
  __asm volatile ("# in int 27");
}

struct vec {
  unsigned char intno;
  unsigned handleroff __attribute__ ((packed));
} vectors[] = { { 0x00, __builtin_ia16_FP_OFF (int0_handler) },
		{ 0x06, __builtin_ia16_FP_OFF (int6_handler) },
		{ 0x19, __builtin_ia16_FP_OFF (int19_handler) },
		{ 0x20, __builtin_ia16_FP_OFF (int20_handler) },
		{ 0x21, __builtin_ia16_FP_OFF (int21_handler) },
		{ 0x24, __builtin_ia16_FP_OFF (int24_handler) },
		{ 0x25, __builtin_ia16_FP_OFF (int25_handler) },
		{ 0x26, __builtin_ia16_FP_OFF (int26_handler) },
		{ 0x27, __builtin_ia16_FP_OFF (int27_handler) } };

void abort (void);

int
main (void)
{
  if ((void *) vectors[0].handleroff != (void *) int0_handler)
    abort ();

  if ((void *) vectors[1].handleroff != (void *) int6_handler)
    abort ();

  if ((void *) vectors[2].handleroff != (void *) int19_handler)
    abort ();

  if ((void *) vectors[3].handleroff != (void *) int20_handler)
    abort ();

  if ((void *) vectors[4].handleroff != (void *) int21_handler)
    abort ();

  if ((void *) vectors[5].handleroff != (void *) int24_handler)
    abort ();

  if ((void *) vectors[6].handleroff != (void *) int25_handler)
    abort ();

  if ((void *) vectors[7].handleroff != (void *) int26_handler)
    abort ();

  if ((void *) vectors[8].handleroff != (void *) int27_handler)
    abort ();

  return 0;
}
