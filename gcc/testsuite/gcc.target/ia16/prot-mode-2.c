/* { dg-options "-mprotected-mode -Os -std=gnu11 --save-temps" } */
/* { dg-do run } */

/* Test whether a PHImode value can be passed as a register parameter to a
   `regparmcall' function.  */

extern void abort (void);

/* These two typedef's really refer to the same type...  */
typedef unsigned __attribute__ ((mode (PHI))) PHI_t;
typedef __typeof__ (__builtin_ia16_selector (8)) SEG_t;

__attribute__ ((regparmcall, noinline)) void
foo (PHI_t a1, SEG_t a2, long a3)
{
  void *frame = __builtin_frame_address (0);

  /* If a1 and a2 are passed in registers, they will be pushed onto our
     newly-created stack frame, _before_ the frame address.  If a1 and a2
     are passed as stack arguments, they will appear after the frame
     address.  */
  if ((void *) &a1 >= frame)
    abort ();

  if ((void *) &a2 >= frame)
    abort ();

  /* a3 should be passed as a stack argument.  */
  if ((void *) &a3 <= frame)
    abort ();
}

int
main (void)
{
  foo (1, 2, 3);
  return 0;
}
