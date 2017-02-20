/* { dg-require-effective-target stdint_types } */

#include <stdint.h>

int __attribute__ ((noinline))
foo (void)
{
  return 123;
}

int_least32_t __attribute__ ((noinline))
bar (void)
{
  int_least32_t c = 1;
  c |= 4294967295 ^ (foo () | 4073709551608);
  return c;
}

int
main ()
{
  if (bar () != 0x83fd4005)
    __builtin_abort ();
}
