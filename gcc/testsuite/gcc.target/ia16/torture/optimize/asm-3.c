/* { dg-do assemble } */
/* { dg-options "--std=gnu11 --save-temps" } */

/* Test that GCC only uses the "N" assembler operand constraint when it is
   appropriate.  */

static inline void
outp (unsigned port, unsigned char value)
{
  __asm volatile ("outb %0, %1" : : "Ral" (value), "Nd" (port));
}

void
tx_com1 (void)
{
  outp (0x3f8, '!');
}

/* { dg-final { scan-assembler "outb %al, %dx" } } */
