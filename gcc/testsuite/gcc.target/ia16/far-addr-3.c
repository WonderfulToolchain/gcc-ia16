/* { dg-do assemble } */
/* { dg-options "-O3 -fno-inline --save-temps" } */

/* Do not allow far address space variables to be created, if we are using
   the default tiny memory model.  */

int __far var = 1;	/* { dg-error " does not support .*far.* static " } */

int
main (void)
{
  return 0;
}
