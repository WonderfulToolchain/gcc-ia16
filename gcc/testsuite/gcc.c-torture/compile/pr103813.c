/* PR middle-end/103813 */
/* { dg-skip-if "Array too big" { ia16-*-* } } */

struct A { char b; char c[0x21000000]; };
struct A d;

int
foo ()
{
  return d.c[0x20000000] || d.c[1];
}
