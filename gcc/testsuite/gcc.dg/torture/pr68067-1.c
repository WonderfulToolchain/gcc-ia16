/* { dg-do run { target { stdint_types } } } */

#include <stdint.h>

int main()
{
  int32_t a = -1;
  static int32_t b = -2147483647 - 1;
  static int32_t c = 0;
  int32_t t = a - (b - c);
  if (t != 2147483647)
    __builtin_abort();
  return 0;
}
