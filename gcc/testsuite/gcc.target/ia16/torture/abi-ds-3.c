/* { dg-options "-ffixed-ds -std=gnu11 -Wall -fno-inline --save-temps" } */
/* { dg-do assemble } */

/* Test that a warning is issued when an `no_assume_ds_data' function calls
   an `assume_ds_data' function and %ds is a fixed register.  */

int puts (const char *);
void abort (void);

volatile int qux = 1;

__attribute__ ((assume_ds_data)) void
foo (unsigned p)
{
  qux = 10;
  __asm volatile ("# 1" : : "e" (__builtin_ia16_selector (p)));
  qux = 11;
}

__attribute__ ((no_assume_ds_data)) void
bar (unsigned p)
{
  qux = 6;

  foo (p);	/* { dg-warning "%ds is fixed" } */

  if (qux != 11)
    abort ();	/* { dg-warning "%ds is fixed" } */
  qux = 7;

  __asm volatile ("# 2" : : "e" (__builtin_ia16_selector (p)));
  qux = 8;

  foo (p);	/* { dg-warning "%ds is fixed" } */
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

  __asm volatile ("# 3" : : "e" (__builtin_ia16_selector (p)));

  if (qux != 3)
    abort ();
  qux = 4;

  bar (p);

  if (qux != 9)
    abort ();
  qux = 5;
}

int
main (void)
{
  baz (0xc000);

  if (qux != 5)
    abort ();

  puts ("Hello world!");
  return 0;
}
