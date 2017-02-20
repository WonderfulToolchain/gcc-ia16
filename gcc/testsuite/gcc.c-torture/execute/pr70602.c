/* PR tree-optimization/70602 */
/* { dg-require-effective-target stdint_types } */

#include <stdint.h>

struct __attribute__((packed)) S
{
  int_least32_t s : 1;
  int_least32_t t : 20;
};

int_least32_t a, b, c;

int
main ()
{
  for (; a < 1; a++)
    {
      struct S e[] = { {0, 9}, {0, 9}, {0, 9}, {0, 0}, {0, 9}, {0, 9}, {0, 9}, 
		       {0, 0}, {0, 9}, {0, 9}, {0, 9}, {0, 0}, {0, 9}, {0, 9}, 
		       {0, 9}, {0, 0}, {0, 9}, {0, 9}, {0, 9}, {0, 0}, {0, 9} };
      b = b || e[0].s;
      c = e[0].t;
    }
  return 0;
}
