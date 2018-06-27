/* { dg-options "-std=gnu11 -mno-callee-assume-ds-data-segment -fno-inline -fno-builtin-puts -fno-builtin-abort --save-temps" } */
/* { dg-do run } */

/* Test that the `assume_ds_data' and `no_assume_ds_data' attributes work
   properly under `-mno-callee-assume-ds-data-segment'.  */

int puts (const char *) __attribute__ ((assume_ds_data));
void abort (void) __attribute__ ((assume_ds_data));

volatile int qux = 1;

__attribute__ ((assume_ds_data)) void
foo (unsigned p)
{
  qux = 10;
  __asm volatile ("# 1" : : "Rds" (__builtin_ia16_selector (p)));
  qux = 11;
}

__attribute__ ((no_assume_ds_data)) void
bar (unsigned p)
{
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

__attribute__ ((assume_ds_data)) int
main (void)
{
  baz (0xc000);

  if (qux != 5)
    abort ();

  puts ("Hello world!");
  return 0;
}
