/* { dg-do assemble } */
/* { dg-skip-if "" { *-*-* }  { "-O0" "-O1" } { "" } } */
/* { dg-options "-std=gnu11 --save-temps" } */

/* Test whether the addition below is compiled into something like
	addw	$2,	(%bx)
   rather than
	movw	(%bx),	%ax
	addw	$2,	%ax
	movw	%ax,	(%bx)
   when optimizing.  This issue was reported by Bart Oldeman --- see
   https://github.com/tkchia/gcc-ia16/issues/15 .  */

void incnear(int *a)
{
  (*a)+=2;
}

/* { dg-final { scan-assembler "addw\[ \\t\]\\\$2,\[ \\t\]\\(%(bx|bp|si|di)\\)" } } */
