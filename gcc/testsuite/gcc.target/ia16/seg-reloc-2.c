/* { dg-do run } */
/* { dg-options "-Os -mcmodel=small --save-temps" } */

/* Test that MZ relocations with addends link and work properly under the
   small code model, even in the presence of far functions and
   __attribute__ ((far_section)) functions.  */

void abort (void);
int puts (const char *);
extern int errno;

/* This should go in the same segment as main ().  */
__attribute__ ((noinline))
static unsigned
cs (void) __far
{
  unsigned x;
  __asm volatile ("movw %%cs, %0 # 1" : "=r" (x) : : "memory");
  return x;
}

/* This should _not_ go in the same segment as main ().  */
__attribute__ ((noinline, far_section))
static unsigned
other_cs (void) __far
{
  unsigned x;
  __asm volatile ("movw %%cs, %0 # 2" : "=r" (x) : : "memory");
  return x;
}

static unsigned
ss (void)
{
  unsigned x;
  __asm volatile ("movw %%ss, %0" : "=r" (x) : : "memory");
  return x;
}

int
main (int argc, char **argv, char **envp)
{
  unsigned p, q, r, s, t, u;

  __asm ("movw $main@SEGMENT16+0x674e, %0" : "=r" (p));

  if (p != cs () + 0x674e)
    abort ();
  if (p == other_cs () + 0x674e)
    abort ();

  __asm ("movw $main@SEGMENT16-0x2329, %0" : "=r" (q));

  if (q != cs () - 0x2329)
    abort ();
  if (q == other_cs () - 0x2329)
    abort ();

  __asm ("movw $other_cs@SEGMENT16+0x0e42, %0" : "=r" (r));

  if (r != other_cs () + 0x0e42)
    abort ();
  if (r == cs () + 0x0e42)
    abort ();

  __asm ("movw $other_cs@SEGMENT16-0x300c, %0" : "=r" (s));

  if (s != other_cs () - 0x300c)
    abort ();
  if (s == cs () - 0x300c)
    abort ();

  __asm ("movw $errno@SEGMENT16+0x3ded, %0" : "=r" (t));

  if (t != ss () + 0x3ded)
    abort ();

  __asm ("movw $errno@SEGMENT16-0x7973, %0" : "=r" (u));

  if (u != ss () - 0x7973)
    abort ();

  puts ("Hello world!");
  return 0;
}

/* Make sure we call other_cs () through `lcall' instructions.  */
/* { dg-final { scan-assembler "lcall\[ \\t\]\\\$.*,\[ \\t]\\\$other_cs" } } */
/* { dg-final { scan-assembler-not "\[^l\]call\[ \\t\]other_cs" } } */
