/* { dg-do run } */
/* { dg-options "-O3 -mcmodel=tiny --save-temps" } */

/* Test that the tiny code model (`-mcmodel=tiny') works.  */

#ifndef __IA16_CMODEL_TINY__
# error
#endif
#ifndef __TINY__
# error
#endif
#ifdef __IA16_CMODEL_SMALL__
# error
#endif
#ifdef __SMALL__
# error
#endif

int puts (const char *);
void abort (void);

#define FP_SEG(fp) \
	((unsigned) ((unsigned long) (void __far *) (fp) >> 16))

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
  static int some_var = 0;
  unsigned main_seg;

  if (cs () != ss ())
    abort ();

  main_seg = FP_SEG (main);

  if (main_seg != FP_SEG (&some_var))
    abort ();

  if (main_seg != FP_SEG (puts))
    abort ();

  if (main_seg != FP_SEG (abort))
    abort ();

  if (main_seg != FP_SEG (&argc))
    abort ();

  if (main_seg != FP_SEG (&argv[0]))
    abort ();

  if (main_seg != FP_SEG (&argv[0][0]))
    abort ();

  if (main_seg != FP_SEG (&envp[0]))
    abort ();

  puts ("Hello world!");
  return 0;
}
