/* { dg-do run } */
/* { dg-options "-mregparmcall -Os -fno-inline -fno-toplevel-reorder --save-temps" } */

/* Check that stack spills near the prologue which can be profitably
   rewritten into pushes are indeed rewritten, when compiling a simple
   `regparmcall' function.  This tests for an issue reported by Bart Oldeman
   --- https://github.com/tkchia/gcc-ia16/issues/48 .  */

int printf (const char *, ...);
void abort (void);
int rand (void);
int foo (int);

int foo (int b)
{
  return rand () ^ b;
}

int bar (int a, int b)
{
  int baz = foo (b);
  return a || baz < b;
}

void dummy (void)
{
}

int main (void)
{
  unsigned bar_size = (char *) dummy - (char *) bar;
  if (bar_size == 0)
    {
      printf ("cannot get size of bar (, )\n");
      abort ();
    }
  /*
	bar:
		pushw	%si
		pushw	%bp
		movw	%sp,	%bp
		pushw	%dx		// N.B.
		xchgw	%ax,	%si
		movw	%dx,	%ax
		call	foo
		cmpw	$1,	%si
		sbbb	%ch,	%ch
		incb	%ch
		movw	-2(%bp),	%dx
		xorb	%cl,	%cl
		cmpw	%ax,	%dx
		jle	.L2
		movb	$1,	%cl
	.L2:
		orb	%cl,	%ch
		movb	%ch,	%al
		xorb	%ah,	%ah
		movw	%bp,	%sp
		popw	%bp
		popw	%si
		ret
   */
  if (bar_size > 0x28)
    {
      printf ("bar (, ) is too large: %#x bytes\n", bar_size);
      abort ();
    }
  return 0;
}

/* { dg-final { scan-assembler-not "movw\[ \\t\]*%dx,\[ \\t\]*\[-0-9\]*\\(%bp\\)" } } */
