/* { dg-do compile { target { stdint_types } } } */
/* { dg-options "-O3" } */

#include <stdint.h>

void *fn1(void *p1, void *p2, intptr_t p3)
{
  intptr_t a = (intptr_t)p1, b = (intptr_t)p2, c = p3;

  while (c)
    {
      int d = ((int *)b)[0];

      c--;
      ((char *)a)[0] = d;
      a++;
    }
  return 0;
}

