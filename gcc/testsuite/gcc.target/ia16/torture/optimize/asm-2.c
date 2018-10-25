/* { dg-do assemble } */
/* { dg-options "--std=gnu11 --save-temps" } */

/* Test that GCC understands the "N" assembler operand constraint.  */

static inline void
outp (unsigned port, unsigned char value)
{
  __asm volatile ("outb %0, %1" : : "Ral" (value), "Nd" (port));
}

void
eoi_pic2 (void)
{
  outp (0xa0, 0x20);
}

/* { dg-final { scan-assembler "outb %al, \\\$160" } } */
