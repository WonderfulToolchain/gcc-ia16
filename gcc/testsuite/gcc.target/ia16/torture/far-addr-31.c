/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that we can cast a far pointer to a near pointer without crashing the
   compiler.

      "	far-addr-31.c: In function `joinMCBs':
	far-addr-31.c:52:1: error: unrecognizable insn:
	 }
	 ^
	(insn 24 23 25 4 (set (subreg:HI (reg:SI 54) 0)
	        (truncate:HI (reg/v/f:SI 26 [ p ]))) far-addr-31.c:45 -1
	     (nil))
	far-addr-31.c:52:1: internal compiler error: in extract_insn, at
	 recog.c:2287 "

   This test case is partly taken a modified version of the FreeDOS kernel
   code (in kernel/memmgr.c).  The FP_OFF (.) definition below triggered a
   bug in GCC in the code for casting far pointers to near pointers.
	-- tkchia */

#define MK_FP(seg, ofs) \
	((void __far *) ((unsigned long) (seg) << 16 | (unsigned) (ofs)))
#define FP_SEG(fp)	\
	((unsigned) ((unsigned long) (void __far *) (fp) >> 16))
#define FP_OFF(fp)	((unsigned) (void *) (fp))

#define nxtMCBsize(mcb, size) \
			MK_FP (FP_SEG (mcb) + (size) - 1, FP_OFF (mcb))
#define nxtMCB(mcb)	nxtMCBsize ((mcb), (mcb)->m_size)
#define mcbFree(mcb)	((mcb)->m_psp == 0)

struct mcb
{
  unsigned char m_type;
  unsigned m_psp, m_size;
  unsigned char m_fill[3], m_name[8];
} __attribute__ ((packed));

int
joinMCBs (unsigned para)
{
  struct mcb __far *p = (struct mcb __far *) MK_FP (para, 0);
  struct mcb __far *q;
  while (p->m_type == 0x4d)
    {
      q = nxtMCB (p);
      if (! mcbFree (q))
	break;
      p->m_type = q->m_type;
      p->m_size += q->m_size + 1;
      q->m_size = 0xffff;
    }
  return 0;
}
