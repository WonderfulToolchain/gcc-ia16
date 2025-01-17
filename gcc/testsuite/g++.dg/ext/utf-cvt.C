/* Contributed by Kris Van Hees <kris.van.hees@oracle.com> */
/* Test the char16_t and char32_t promotion rules. */
/* { dg-do compile { target c++11 } } */
/* { dg-options "-Wall -Wconversion -Wsign-conversion -Wsign-promo" } */

#ifndef __INT_LEAST32_TYPE__
#define __INT_LEAST32_TYPE__ int
#endif

extern void f_c (char);
extern void fsc (signed char);
extern void fuc (unsigned char);
extern void f_s (short);
extern void fss (signed short);
extern void fus (unsigned short);
extern void f_i (__INT_LEAST32_TYPE__);
extern void fsi (signed __INT_LEAST32_TYPE__);
extern void fui (unsigned __INT_LEAST32_TYPE__);
extern void f_l (long);
extern void fsl (signed long);
extern void ful (unsigned long);
extern void f_ll (long long);
extern void fsll (signed long long);
extern void full (unsigned long long);

void m(char16_t c0, char32_t c1)
{
    f_c (c0);	/* { dg-warning "alter its value" } */
    fsc (c0);	/* { dg-warning "alter its value" } */
    fuc (c0);	/* { dg-warning "alter its value" } */
    f_s (c0);	/* { dg-warning "change the sign" } */
    fss (c0);	/* { dg-warning "change the sign" } */
    fus (c0);
    f_i (c0);
    fsi (c0);
    fui (c0);
    f_l (c0);
    fsl (c0);
    ful (c0);
    f_ll (c0);
    fsll (c0);
    full (c0);

    f_c (c1);	/* { dg-warning "alter its value" } */
    fsc (c1);	/* { dg-warning "alter its value" } */
    fuc (c1);	/* { dg-warning "alter its value" } */
    f_s (c1);	/* { dg-warning "alter its value" } */
    fss (c1);	/* { dg-warning "alter its value" } */
    fus (c1);	/* { dg-warning "alter its value" } */
    f_i (c1);	/* { dg-warning "change the sign" } */
    fsi (c1);	/* { dg-warning "change the sign" } */
    fui (c1);
    f_l (c1);	/* { dg-warning "change the sign" "" { target { llp64 || { ilp32 || ia16-*-* } } } } */
    fsl (c1);	/* { dg-warning "change the sign" "" { target { llp64 || { ilp32 || ia16-*-* } } } } */
    ful (c1);
    f_ll (c1);
    fsll (c1);
    full (c1);
}
