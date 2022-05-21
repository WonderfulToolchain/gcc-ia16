/* { dg-options "-std=gnu11 -fno-inline --save-temps" } */
/* { dg-additional-sources "support/no-ss-data-main.S" } */
/* { dg-do run } */

/* Test that the `no_assume_ss_data' works properly & does not crash the
   compiler.  This bug was reported by Adrian Siekierka, & the test case comes
   from libgcc code --- see https://github.com/tkchia/gcc-ia16/issues/102 . */

typedef unsigned int UQItype __attribute__ ((mode (QI)));
typedef unsigned int UHItype, UWtype __attribute__ ((mode (HI)));
#define W_TYPE_SIZE	(sizeof(UWtype) * __CHAR_BIT__)

extern void abort (void);

const UQItype popcount_tab[256] =
{
    0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
};

__attribute__((noinline, no_assume_ss_data)) int
popcounthi2_no_ss_data (UWtype x)
{
  int i, ret = 0;

  for (i = 0; i < W_TYPE_SIZE; i += 8)
    ret += popcount_tab[(x >> i) & 0xff];

  return ret;
}

__attribute__ ((no_assume_ss_data)) int
do_stuff (void)
{
  if (popcounthi2_no_ss_data (0x0000) != 0)
    return 1;
  if (popcounthi2_no_ss_data (0x0080) != 1)
    return 1;
  if (popcounthi2_no_ss_data (0x0200) != 1)
    return 1;
  if (popcounthi2_no_ss_data (0x00ff) != 8)
    return 1;
  if (popcounthi2_no_ss_data (0xffff) != 16)
    return 1;
  if (popcounthi2_no_ss_data (0x7fff) != 15)
    return 1;
  if (popcounthi2_no_ss_data (0xdfff) != 15)
    return 1;
  return 0;
}

int
check_stuff (void)
{
  return 0;
}
