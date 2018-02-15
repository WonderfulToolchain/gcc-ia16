/* { dg-do assemble } */
/* { dg-xfail-if "" *-*-* } */
/* { dg-options "-mrtd -Os --save-temps" } */

/* XFAIL: the `cdecl' and `stdcall' attributes do not mix.  */

__attribute__ ((stdcall, cdecl)) unsigned
inc (unsigned x)
{
  return x + 1;
}
