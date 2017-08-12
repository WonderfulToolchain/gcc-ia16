/* { dg-do run } */
/* { dg-options "-O3 -fno-inline --save-temps" } */

/* Can we cast a generic pointer to a far pointer --- and back?  */

#define VALUE1	0x1337b33fu
#define VALUE2	0xb3effe3du
#define VALUE3	0xcafe13e7u

int printf (const char *, ...);
void abort (void);

static volatile unsigned long var = VALUE1;

volatile unsigned long __far *
p_var (void)
{
  return (volatile unsigned long __far *) &var;
}

int main (void)
{
  volatile unsigned long __far *p = p_var ();
  volatile unsigned long *q;

  if (*p != VALUE1)
    abort ();

  var = VALUE2;
  if (*p != VALUE2)
    abort ();

  q = (volatile unsigned long *)p;
  *p = VALUE3;
  if (*q != VALUE3)
    abort ();

  return 0;
}
