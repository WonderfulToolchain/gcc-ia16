/* { dg-do assemble } */
/* { dg-skip-if "" lto } */
/* { dg-xfail-if "" *-*-* } */
/* { dg-options "--std=gnu11 --save-temps" } */

/* XFAIL: GCC should not treat e.g. "ax" in the clobber list as meaning that
   only %al is clobbered.

   I found this bug in gcc-ia16 20180822, while fixing another bug in FreeDOS
   command.com (https://github.com/FDOS/freecom/pull/2#event-1808796470).
   -- tkchia  */

void
close_fd (int fd)
{
  /* This should fail with "`asm' operand has impossible constraints".  */
  __asm volatile ("int $0x21" : /* no outputs */
			      : "Rah" ((char) 0x3e), "b" (fd)
			      : "ax");
}
