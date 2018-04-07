/* { dg-options "-mcmodel=small -std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that we can pass an absolute-address far pointer as a parameter a
   function.

   This test case is partly taken from the FreeDOS kernel code (in
   kernel/main.c).  It triggered a bug in GCC which I introduced when I
   added support for far static variables.  -- tkchia  */

#define MK_FP(seg, ofs) \
	((void __far *) ((unsigned long) (seg) << 16 | (unsigned) (ofs)))

typedef struct {
  unsigned char xx1[0x18];
  unsigned char ps_files[0x14];
  unsigned char xx2[0xd4];
} psp;

void fmemset (void __far *, int, unsigned) __attribute__ ((cdecl));

void
PSPInit (void)
{
  psp __far *p = MK_FP (0x60, 0);
  fmemset (p->ps_files, 0xff, 20);
}
