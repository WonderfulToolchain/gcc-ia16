/* { dg-do compile } */
/* { dg-options "-march=i8086" } */

/* Test whether architecture-specific macros are defined and undefined
   correctly when `-march=i8086' is specified.  */

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
#ifdef __IA16_FEATURE_FSTSW_AX
# error
#endif
#ifdef __IA16_ARCH_ANY_186
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
#ifndef __IA16_FEATURE_AAD_IMM
# error
#endif
#ifndef __IA16_ARCH_I8086
# error
#endif

/* (Other macros such as __IA16_ARCH_I8088 may be either defined or
   undefined without affecting the correctness of operations too much...) */

int
main (void)
{
  return 0;
}
