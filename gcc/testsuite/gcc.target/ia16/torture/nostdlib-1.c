/* { dg-options "-nostdlib --save-temps" } */
/* { dg-do run } */

/* Test that we can use the -nostdlib option to build programs that do not
   use the default startup modules and C libraries.  */

#ifdef __IA16_CMODEL_IS_FAR_TEXT
__attribute__ ((section (".text")))	/* FIXME: remove the need for this */
#endif
void
_start (void)
{
  __asm volatile ("int $0x21" : : "a" (0x4c00u) : "memory");
  __builtin_unreachable ();
}
