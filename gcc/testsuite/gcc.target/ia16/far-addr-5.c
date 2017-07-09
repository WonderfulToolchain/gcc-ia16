/* { dg-do run } */
/* { dg-options "-O3 --save-temps" } */

/* Do something non-trivial with far pointers.

   Assume that we are running with a PC-compatible ROM BIOS.  If we obtain
   the clock tick count at 0x0040:0x006c and compare it to the clock tick
   count obtained by the BIOS software interrupt $0x1a, they should be the
   same (after a few tries, at least).

   Reference:  www.ctyme.com/intr/rb-2271.htm  */

static unsigned long
irq0_clock_ticks1 (void)
{
  unsigned ticks_hi, ticks_lo, midnight;
  unsigned long ticks;
  __asm ("int $0x1a"
    : "=c" (ticks_hi), "=d" (ticks_lo), "=a" (midnight)
    : "2" (0x0000u)
    : "bx", "cc", "memory");
  ticks = (unsigned long) ticks_hi << 16 | ticks_lo;
  return ticks;
}

static unsigned long
irq0_clock_ticks2 (void)
{
  volatile unsigned long __far *p =
    (volatile unsigned long __far *) 0x0040006c;
  return *p;
}

int
main (void)
{
  unsigned i;
  for (i = 0; i < 100; ++i)
    {
      unsigned long ticks1 = irq0_clock_ticks1 ();
      unsigned long ticks2 = irq0_clock_ticks2 ();
      if (ticks1 == ticks2)
	return 0;
    }
  return 1;
}
