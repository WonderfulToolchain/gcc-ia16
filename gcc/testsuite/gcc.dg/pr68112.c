/* { dg-do compile { target { stdint_types } } } */
/* { dg-options "-O2 -Waggressive-loop-optimizations" } */

#include <stdint.h>

int_least32_t *a;

void
foo ()
{
  for (int_least32_t i = 0; i < 65536; i++)
    *a = i << 24;
}
