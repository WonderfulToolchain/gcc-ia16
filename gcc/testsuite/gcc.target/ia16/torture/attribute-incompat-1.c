/* { dg-options "-std=gnu11 -Wall --save-temps" } */
/* { dg-do assemble } */

/* Test that warnings are issued when one tries to assign a function pointer
   to a pointer variable with incompatible function attributes.

   Also check if certain pairs of different type attribute sets which should
   be compatible are, in fact, considered compatible.  */

#if defined __IA16_CALLCVT_CDECL
int (*p1) (int) __attribute__ ((cdecl));
int (*p2) (int) __attribute__ ((stdcall));
int (*p3) (int) __attribute__ ((regparmcall));
#elif defined __IA16_CALLCVT_STDCALL
int (*p1) (int) __attribute__ ((stdcall));
int (*p2) (int) __attribute__ ((regparmcall));
int (*p3) (int) __attribute__ ((cdecl));
#else
int (*p1) (int) __attribute__ ((regparmcall));
int (*p2) (int) __attribute__ ((cdecl));
int (*p3) (int) __attribute__ ((stdcall));
#endif
int (*p4) (int) __attribute__ ((assume_ds_data));
int (*p5) (int) __attribute__ ((no_assume_ds_data));
int (*p6) (int) __far;
int (*p7) (int) __far __attribute__ ((near_section));
int (*p8) (int) __far __attribute__ ((far_section));

void f1 (int (*p) (int))
{
  p1 = p;
}

void f2 (int (*p) (int))
{
  p2 = p;  /* { dg-warning "assignment from incompatible pointer type" } */
}

void f3 (int (*p) (int))
{
  p3 = p;  /* { dg-warning "assignment from incompatible pointer type" } */
}

void f4 (int (*p) (int))
{
  p4 = p;
}

void f5 (int (*p) (int))
{
  p5 = p;  /* { dg-warning "assignment from incompatible pointer type" } */
}

void f6 (int (*p) (int) __far)
{
  p6 = p;
}

void f6a (int (*p) (int) __far __attribute__ ((far_section)))
{
  p6 = p;
}

void f7 (int (*p) (int) __far)
{
  p7 = p;  /* { dg-warning "assignment from incompatible pointer type" } */
}

void f8 (int (*p) (int) __far)
{
  p8 = p;
}
