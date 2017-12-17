/* { dg-do assemble } */
/* { dg-options "-O3 --save-temps" } */

/* Test whether we rewrite
	incb	%al
   into
	incw	%ax
   as appropriate, when optimizing.  */

char foo (char x)
{
  return x + 1;
}

/* { dg-final { scan-assembler "incw\[ \\t\]%ax" } } */
