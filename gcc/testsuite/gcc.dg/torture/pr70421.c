/* PR target/70421 */
/* { dg-do run { target { stdint_types } } } */
/* { dg-additional-options "-Wno-psabi -w" } */

#include <stdint.h>

typedef uint32_t V __attribute__ ((vector_size (64)));

uint_least32_t __attribute__ ((noinline, noclone))
foo (uint_least32_t x, V u, V v)
{
  v[1] ^= v[2];
  x ^= ((V) v)[u[0]];
  return x;
}

int
main ()
{
  uint_least32_t x = foo (0x10, (V) { 1 }, (V) { 0x100, 0x1000, 0x10000 });
  if (x != 0x11010)
    __builtin_abort ();
  return 0;
}
