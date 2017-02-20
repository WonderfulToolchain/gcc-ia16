/* { dg-do compile { target { stdint_types } } } */
/* { dg-options "-O1 -Wall" } */
/* PR/70013, SRA of constant-pool loads removes initialization of part of d.  */

#include <stdint.h>
#include <inttypes.h>

#pragma pack (1)
struct S0 {
  uint_least32_t f0 : 17;
};

int_least32_t c;

int
main (int argc, char **argv)
{
  struct S0 d[] = { { 1 }, { 2 } };
  struct S0 e = d[1];

  c = d[0].f0;
  __builtin_printf (PRIxLEAST32 "\n", e.f0);
  return 0;
}
