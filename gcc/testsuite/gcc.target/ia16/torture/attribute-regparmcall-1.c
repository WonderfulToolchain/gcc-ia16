/* { dg-do assemble } */
/* { dg-options "--std=gnu11 -Wall --save-temps" } */

/* Do some basic tests to make sure that __attribute__ ((regparmcall)) does
   not make GCC weird out.  */

__attribute__ ((regparmcall)) int
sort_of_printf (const char *, ...);

typedef struct {
  int x, y, z;
} xyz_t;

__attribute__ ((regparmcall)) xyz_t
frob1 (xyz_t xyz)
{
  return xyz;
}

__attribute__ ((regparmcall)) unsigned long
frob2 (unsigned x, unsigned long y, unsigned long z)
{
  return x + y + z;
}

__attribute__ ((regparmcall)) unsigned long long
frob3 (unsigned long long x)
{
  return x + 1;
}

__attribute__ ((regparmcall)) unsigned long
frob4 (unsigned long x, unsigned long y)
{
  return x + y;
}

__attribute__ ((regparmcall)) float
frob5 (float x)
{
  return x + 1;
}

__attribute__ ((regparmcall)) double
frob6 (double x)
{
  return x + 1;
}

__attribute__ ((regparmcall)) void
frob7 (int x)
{
  sort_of_printf ("%d\n", x);
}

__attribute__ ((regparmcall)) unsigned long long
frob8 (int x, ...)
{
  return x;
}
