/* { dg-do assemble } */
/* { dg-skip-if "" { *-*-* }  { "-O0" } { "" } } */
/* { dg-options "-std=gnu11 --save-temps" } */

/* Test for a bogus register spill just before sign-extending a value in %al
   into %ax (especially when compiling with the -mregparmcall option):
	movb	%al,	-1(%bp)
	cbtw
   This isue was reported by Bart Oldeman --- see https://github.com/tkchia/
   gcc-ia16/issues/31 .  */

struct j {
  char j;
};

struct a {
  unsigned char flag;
  struct j __far *pj;
};

extern struct a __far *fnc (int i, int j);

void
foo (struct j __far * pj)
{
  struct a __far *p = fnc (0, pj->j);
  if (p)
    {
      p->flag &= ~1;
      p->pj = pj;
    }
}

/* { dg-final { scan-assembler-not "movb\[ \\t\]%al,\[ \\t\].*\\(%bp\\)" } } */
