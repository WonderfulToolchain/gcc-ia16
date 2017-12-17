/* { dg-do assemble } */
/* { dg-options "-Os --save-temps" } */

/* Test whether we rewrite
	movw	%dx,	%ax
   into
	xchgw	%ax,	%dx
   as appropriate, when optimizing for size.  */

unsigned long foo (void);

unsigned bar (void)
{
  return foo () >> 16;
}

/* { dg-final { scan-assembler "xchgw\[ \\t\]%ax,\[ \\t\]%dx" } } */
