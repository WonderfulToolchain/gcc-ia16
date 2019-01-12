/* { dg-options "-nostdlib --save-temps" } */
/* { dg-do run } */

/* Test that we can use the -nostdlib option to build programs that do not
   use the default startup modules and C libraries.  */

void
_start (void)
{
  unsigned ax;
  __asm volatile ("int $0x21" : : "a" (0x4c00u) : "memory");
  __builtin_unreachable ();
}
