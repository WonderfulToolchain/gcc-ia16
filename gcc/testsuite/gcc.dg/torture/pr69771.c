/* PR rtl-optimization/69771 */
/* { dg-do compile { target { stdint_types } } } */

#include <stdint.h>

unsigned char a = 5, c;
unsigned short b = 0;
uint32_t d = 0x76543210;

void
foo (void)
{
  c = d >> ~(a || ~b);	/* { dg-warning "shift count is negative" "" { target { ! ia16-*-* } } } */
}
