/* { dg-do run } */
/* { dg-options "-Os -mcmodel=small --save-temps" } */

/* Test that MZ relocations with addends link and work properly under the
   small code model.  This tests for an issue reported by Bart Oldeman ---
   https://github.com/tkchia/gcc-ia16/issues/22 .  */

void abort (void);
int puts (const char *);
extern char **environ;

static unsigned
cs (void)
{
  unsigned x;
  __asm ("movw %%cs, %0" : "=r" (x));
  return x;
}

static unsigned
ss (void)
{
  unsigned x;
  __asm ("movw %%ss, %0" : "=r" (x));
  return x;
}

int
main (int argc, char **argv, char **envp)
{
  unsigned p, q, r, s;

  __asm ("movw $main@SEGMENT16+0x674e, %0" : "=r" (p));

  if (p != cs () + 0x674e)
    abort ();

  __asm ("movw $main@SEGMENT16-0x2329, %0" : "=r" (q));

  if (q != cs () - 0x2329)
    abort ();

  __asm ("movw $environ@SEGMENT16+0x3ded, %0" : "=r" (r));

  if (r != ss () + 0x3ded)
    abort ();

  __asm ("movw $environ@SEGMENT16-0x7973, %0" : "=r" (s));

  if (s != ss () - 0x7973)
    abort ();

  puts ("Hello world!");
  return 0;
}
