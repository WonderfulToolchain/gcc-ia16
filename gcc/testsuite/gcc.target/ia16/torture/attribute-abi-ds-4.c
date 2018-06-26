/* { dg-options "-std=gnu11 -fcall-saved-ds -fno-inline -Wall --save-temps" } */
/* { dg-do assemble } */

/* Test that the `assume_ds_data' and `no_assume_ds_data' attributes trigger
   warnings when %ds is a call-saved register.  */

int puts (const char *);
void abort (void);

volatile int qux = 1;

__attribute__ ((assume_ds_data)) void
foo (unsigned p)
{			/* { dg-warning "%ds is a call-saved register" } */
  qux = 10;
  __asm volatile ("# 1" : : "Rds" (__builtin_ia16_selector (p)));
  qux = 11;
}

__attribute__ ((no_assume_ds_data)) void
bar (unsigned p)
{			/* { dg-warning "%ds is a call-saved register" } */
  qux = 6;

  foo (p);

  if (qux != 11)
    abort ();
  qux = 7;

  __asm volatile ("# 2" : : "Rds" (__builtin_ia16_selector (p)));

  if (qux != 7)
    abort ();
  qux = 8;

  foo (p);

  if (qux != 11)
    abort ();
  qux = 9;
}

void
baz (unsigned p)
{
  if (qux != 1)
    abort ();
  qux = 2;

  bar (p);

  if (qux != 9)
    abort ();
  qux = 3;

  __asm volatile ("# 3" : : "Rds" (__builtin_ia16_selector (p)));

  if (qux != 3)
    abort ();
  qux = 4;

  bar (p);

  if (qux != 9)
    abort ();
  qux = 5;
}
