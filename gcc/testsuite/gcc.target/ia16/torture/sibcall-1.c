/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do run } */

/* Test that sibling calls (tail calls) work properly.

   In particular, a sibcall that needs to cross a segment boundary --- e.g. 
   the medium memory model is used, and the callee is a weak, or the
   compilation uses -ffunction-sections --- should be optimized to a far
   jump, never a near jump.

   See the discussion under https://github.com/tkchia/gcc-ia16/issues/73 .
	-- tkchia  */

extern int printf (const char *, ...);

__attribute__ ((noinline)) static int
f1 (void)
{
  __asm volatile (".rept 0x100; nop; .endr");
  printf ("Hello world!\n");
  __asm volatile (".rept 0x100; nop; .endr");
  return 0;
}

__attribute__ ((noinline)) static int
f2 (void)
{
  __asm volatile (".rept 0x100; nop; .endr");
  return f1 ();
}

__attribute__ ((noinline)) static int
f3 (void)
{
  __asm volatile (".rept 0x100; nop; .endr");
  return f2 ();
}

__attribute__ ((noinline)) static int
f4 (void)
{
  __asm volatile (".rept 0x100; nop; .endr");
  return f3 ();
}

int
main (void)
{
  __asm volatile (".rept 0x100; nop; .endr");
  return f4 ();
}
