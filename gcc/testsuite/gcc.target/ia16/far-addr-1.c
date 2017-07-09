/* { dg-do compile } */
/* { dg-options "-O3 -fno-inline --save-temps" } */

/* Test for basic far pointer functionality. */

unsigned long
irq0_clock_ticks (void)
{
  volatile unsigned long __far *p =
    (volatile unsigned long __far *) 0x0040006C;
  return *p;
}
/* { dg-final { scan-assembler "movw\[ \\t\]%\[de\]s:" } } */
