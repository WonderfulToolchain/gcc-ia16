/* { dg-do assemble } */
/* { dg-options "-O3 --save-temps" } */

/* Test that `xlat' instructions are prefixed with the proper segment override
   if %ds != %ss and if we are optimizing.  */

void abort (void);

unsigned char
foo (unsigned char x)
{
  static unsigned char map[] = "0123456789abcdef";

  __asm volatile ("" : : "a" (x), "b" (map), "Rds" (0));
  return map[x];
}

/* { dg-final { scan-assembler "xlat\[ \\t\]%ss:" } } */
