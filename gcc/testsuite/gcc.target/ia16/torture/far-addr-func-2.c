/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/* Test if the compiler can emit an `lcall' with an absolute address.  */

typedef void func_t (void);
typedef func_t __far far_func_t;

void reset_video (void)
{
  ((far_func_t *) 0xc0000003ul) ();
}

/* { dg-final { scan-assembler "lcall\[ \\t\]\\\$49152,\[ \\t]\\\$3" } } */
