/* { dg-do assemble } */
/* { dg-options "-O3 -fno-inline --save-temps" } */

/* Check that speed optimizations work correctly when compiling a simple
   function involving a far pointer.  */

void incfar (int __far *a)
{
  *a += 2;
}

/* { dg-final { scan-assembler-times "lesw" 1 } } */
/* { dg-final { scan-assembler-not "mov\[ \\t\].*,\[ \\t\]%es" } } */
