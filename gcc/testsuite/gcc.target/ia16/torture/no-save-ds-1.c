/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do run } */

/* Test that the no_save_ds function attribute works.  */

void abort (void);

__attribute__ ((noinline, no_assume_ds_data)) static unsigned
foo (void)
{
  unsigned v;
  __asm volatile ("movw %%ds, %0" : "=r" (v)
				  : "Rds" (__builtin_ia16_selector (0x73d5)));
  return v;
}

__attribute__ ((noinline, no_assume_ds_data, no_save_ds)) static unsigned
bar (void)
{
  unsigned v;
  __asm volatile ("movw %%ds, %0" : "=r" (v)
				  : "Rds" (__builtin_ia16_selector (0x1709)));
  return v;
}

int main (void)
{
  static volatile unsigned baz = 0xda16, qux = 0x350d;

  if (foo () != 0x73d5)
    abort ();
  if (baz != 0xda16)
    abort ();
  if (bar () != 0x1709)
    abort ();
  if (qux != 0x350d)
    abort ();
  return 0;
}
