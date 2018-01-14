/* { dg-do run } */
/* { dg-options "-Os -fno-inline -fno-toplevel-reorder --save-temps" } */

/* Check that size optimizations work correctly when compiling a simple
   function involving a far pointer.  Also try to check that there are no
   size regressions.  */

int printf (const char *, ...);
void abort (void);

void incfar (int __far *a)
{
  *a += 2;
}

void dummy (void)
{
}

int main (void)
{
  unsigned incfar_size = (char *) dummy - (char *) incfar;
  if (incfar_size == 0)
    {
      printf ("cannot get size of incfar (.)\n");
      abort ();
    }
  /*
	incfar:
		pushw	%es
		pushw	%bp
		movw	%sp,	%bp
		subw	$2,	%sp
		lesw	6(%bp),	%bx
		addw	$2,	%es:(%bx)
		movw	%bp,	%sp
		popw	%bp
		popw	%es
		ret
   */
  if (incfar_size > 0xe)
    {
      printf ("incfar (.) is too large: %#x bytes\n", incfar_size);
      abort ();
    }
  return 0;
}

/* { dg-final { scan-assembler-times "l\[de\]sw" 1 } } */
/* { dg-final { scan-assembler-not "mov\[ \\t\].*,\[ \\t\]%\[de\]s" } } */
