/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Can we copy a moderately big, constant-size structure from one far
   address to another (or between a near address and a far address)?  See
   https://github.com/tkchia/gcc-ia16/issues/12 .  */

typedef struct { char f[64]; } T;
typedef struct { char f[65]; } U;

void foo (T __far *p, T __far *q)
{
  *p = *q;
}

void bar (T __far *p, T *q)
{
  *p = *q;
}

void baz (T *p, T __far *q)
{
  *p = *q;
}

void qux (U __far *p1, U __far *p2, U *p3, U __far *q1, U *q2, U __far *q3)
{
  *p1 = *q1;
  *p2 = *q2;
  *p3 = *q3;
}

/* Also check that near-to-near copies continue to work even when we have
   implemented "movmemhi".  */
void quux (T *p4, U *p5, T *q4, U *q5)
{
  *p4 = *q4;
  *p5 = *q5;
}
