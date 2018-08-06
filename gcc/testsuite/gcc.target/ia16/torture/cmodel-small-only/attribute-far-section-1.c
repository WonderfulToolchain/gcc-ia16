/* { dg-do assemble } */
/* { dg-options "--std=gnu11 -Wall --save-temps" } */

/* A far_section function should not call a near function.  GCC should flag
   a warning if a program tries to do this.  */

int puts (const char *);

__attribute__ ((far_section)) void __far
hello (void)
{
  puts ("Hello world!");  /* { dg-warning "calling near function from" } */
}
