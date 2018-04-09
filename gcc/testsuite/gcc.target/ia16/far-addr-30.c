/* { dg-do assemble } */
/* { dg-options "-O3 -fno-inline --save-temps" } */

/* Do not allow far address space variables to be manipulated, if we are
   using the default tiny memory model.  */

int printf (const char *, ...);

static int __far var = 1;

int __far *
p_var (void)
{
  return &var;			/* { dg-error " does not support MZ " } */
}

int
main (void)
{
  printf ("%d\n", *p_var ());
  return 0;
}
