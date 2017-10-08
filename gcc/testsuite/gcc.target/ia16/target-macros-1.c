/* { dg-do compile } */
/* { dg-options "-march=any" } */

/* Test whether architecture-specific macros are defined and undefined
   correctly when `-march=any' is specified.  */

/* These macros absolutely must be undefined.  */
#ifdef __IA16_FEATURE_SHIFT_IMM
# error
#endif
#ifdef __IA16_FEATURE_PUSH_IMM
# error
#endif
#ifdef __IA16_FEATURE_IMUL_IMM
# error
#endif
#ifdef __IA16_FEATURE_PUSHA
# error
#endif
#ifdef __IA16_FEATURE_ENTER_LEAVE
# error
#endif
#ifdef __IA16_FEATURE_SHIFT_MASKED
# error
#endif
#ifdef __IA16_FEATURE_AAD_IMM
# error
#endif
#ifdef __IA16_FEATURE_FSTSW_AX
# error
#endif
#ifdef __IA16_ARCH_I8086
# error
#endif
#ifdef __IA16_ARCH_I8088
# error
#endif
#ifdef __IA16_ARCH_NEC_V30
# error
#endif
#ifdef __IA16_ARCH_NEC_V20
# error
#endif
#ifdef __IA16_ARCH_I80186
# error
#endif
#ifdef __IA16_ARCH_I80188
# error
#endif
#ifdef __IA16_ARCH_I80286
# error
#endif

/* These macros absolutely must be defined.  */
#ifndef __IA16_ARCH_ANY
# error
#endif

int
main (void)
{
  return 0;
}
