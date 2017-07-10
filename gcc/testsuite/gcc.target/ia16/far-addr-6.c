/* { dg-do run } */
/* { dg-xfail-run-if "" *-*-* } */
/* { dg-options "-O3 -fno-inline --save-temps" } */

/* FAIL: Can we cast a generic pointer to a far pointer?  Currently the
   compiler sort of allows it (with a warning), but the resulting pointer is
   bogus.  */

#define VALUE	0x1337b33fu

int printf (const char *, ...);
void abort (void);

static volatile unsigned long var = VALUE;

volatile unsigned long __far *
p_var (void)
{
  return (volatile unsigned long __far *) &var;
}

int main (void)
{
  volatile unsigned long __far *p = p_var ();
  if (*p != VALUE)
    abort ();
  return 0;
}
