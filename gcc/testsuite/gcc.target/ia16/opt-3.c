/* { dg-do assemble } */
/* { dg-options "-Os --save-temps" } */

/* Test whether we rewrite
	movw	%ax,	%dx
   into
	xchgw	%ax,	%dx
   as appropriate, when optimizing for size.  */

unsigned long foo (void);

unsigned long bar (void)
{
  return foo () << 16 | 0x1234;
}

/* { dg-final { scan-assembler "xchgw\[ \\t\]%ax,\[ \\t\]%dx" } } */
