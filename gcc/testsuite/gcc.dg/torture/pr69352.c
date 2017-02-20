/* { dg-do compile { target { stdint_types } } } */

#include <stdint.h>

intptr_t a[10][14];
int b, c, d, e, f, g, h, i;
void bar (void);
int
foo (int x)
{
  unsigned j;
  int k = 0;
  intptr_t l;
  int m;
  if (h)
    m = 12;
  else
    m = 13;
  if (a[x][m])
    l = (intptr_t) foo;
  a[x][i] = l;
  while (c)
    {
      if (b)
	{
	  if (f)
	    k = 1;
	  bar ();
	}
      for (; d;)
	j++;
    }
  while (c)
    {
      if (a[x][12])
	{
	  if (g)
	    k = 1;
	  j++;
	}
      c = e;
    }
  return k;
}
