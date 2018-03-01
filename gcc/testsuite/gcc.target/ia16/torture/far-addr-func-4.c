/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test that the postfix __far syntax for declaring far functions works.  */

void
reset_video (void)
{
  ((void (*) (void) __far) 0xc0000003ul) ();
}

/* { dg-final { scan-assembler "lcall\[ \\t\]\\\$49152,\[ \\t]\\\$3" } } */
