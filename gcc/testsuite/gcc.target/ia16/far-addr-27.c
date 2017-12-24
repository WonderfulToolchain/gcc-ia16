/* { dg-do run } */
/* { dg-options "-Os -fno-inline -fno-toplevel-reorder --save-temps" } */

/* Check that size optimizations work correctly when compiling a loop.  Also
   try to check that there are no size regressions.  */

int printf (const char *, ...);
void abort (void);

unsigned long
hash1 (void)
{
  unsigned __far *p = (unsigned __far *) 0xfff00000ul;
  unsigned i;
  unsigned long h = 0;
  for (i = 0; i < 0x80u; ++i)
    h = 5 * h ^ *p++;
  return h;
}

__attribute__ ((optimize ("O0")))
unsigned long
hash2 (void)
{
  unsigned __far *p = (unsigned __far *) 0xfff00000ul;
  unsigned i;
  unsigned long h = 0;
  for (i = 0; i < 0x80u; ++i)
    h = 5 * h ^ *p++;
  return h;
}

int
main (void)
{
  unsigned long h1 = hash1 (), h2 = hash2 ();
  unsigned hash1_size = (char *) hash2 - (char *) hash1;
  printf ("%#lx %#lx\n", h1, h2);
  if (h1 != h2)
    abort ();
  if (hash1_size == 0)
    {
      printf ("cannot get size of hash1 ()\n");
      abort ();
    }
  /*
	hash1:
		pushw	%si
		pushw	%di
		pushw	%es
		pushw	%bp
		movw	%sp,	%bp
		pushw	%ds
		pushw	%ds
		movw	$128,	%si
		movw	$0,	-4(%bp)
		xorw	%cx,	%cx
		movw	%cx,	%bx
		movw	$-16,	%ax
		movw	%ax,	%es
		movw	$5,	%di
	.L2:
		movw	$5,	%ax
		mulw	%cx
		movw	%ax,	%cx
		movw	-4(%bp),	%ax
		mulw	%di
		movw	%ax,	-4(%bp)
		movw	%dx,	-2(%bp)
		addw	%dx,	%cx
		xorw	%es:(%bx),	%ax
		movw	%ax,	-4(%bp)
		addw	$2,	%bx
		decw	%si
		jne	.L2
		movw	%cx,	%dx
		movw	%bp,	%sp
		popw	%bp
		popw	%es
		popw	%di
		popw	%si
		ret
   */
  if (hash1_size > 0x45)
    {
      printf ("hash1 () is too large: %#x bytes\n", hash1_size);
      abort ();
    }
  return 0;
}
