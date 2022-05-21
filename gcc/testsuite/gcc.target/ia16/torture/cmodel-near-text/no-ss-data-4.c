/* { dg-options "-std=gnu11 -fno-inline --save-temps" } */
/* { dg-additional-sources "support/no-ss-data-main.S" } */
/* { dg-do run } */

/* Test that we can use va_list, va_start, va_arg, & va_end with
   no_assume_ss_data.  See https://github.com/tkchia/gcc-ia16/issues/104 . */

#include <stdarg.h>

__attribute__((noinline, no_assume_ss_data)) unsigned
baz (const char *fmt, ...)
{
  va_list ap;
  unsigned foo = 0, bar;
  va_start (ap, fmt);
  while ((bar = va_arg(ap, unsigned)) != 0)
    foo ^= bar;
  va_end (ap);
  return foo;
}

__attribute__ ((no_assume_ss_data)) int
do_stuff (void)
{
  unsigned foo = baz ("%#x\n", 0x5bf9u, 0xadbcu, 0x9d11u, 0x5d9cu, 0u);
  if (foo != 0x36c8u)
    return 1;
  return 0;
}

int
check_stuff (void)
{
  return 0;
}
