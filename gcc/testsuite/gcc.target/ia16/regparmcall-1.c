/* { dg-do run } */
/* { dg-options "-mregparmcall -Os --save-temps" } */

/* Test whether the `-mregparmcall' switch works correctly and links with the
   correct libgcc and newlib multilibs.  */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

volatile unsigned long long quotient = 0x55bde67343803983ull,
			    divisor = 0x1670107447a23170ull;

unsigned
inc (unsigned x)
{
  return x + 1;
}

int
main (int argc, char **argv)
{
  unsigned i;
  int fd;

  /* If this code is linked against the wrong libgcc, this loop will
     eventually cause a stack overflow and corrupt the data area.  */
  for (i = 0; i < 10000; ++i)
    {
      unsigned long long mod = quotient % divisor;
      if (mod != 0x126db5166c99a533ull)
	abort ();
    }

  /* Try to open the binary for this program itself to run further tests. 
     If the opening fails, just skip the tests...  */
  fd = open (argv[0], O_RDONLY);
  if (fd == -1)
    return 0;

  /* If this code is linked against the wrong newlib, or if this code and
     newlib are compiled with different ideas of what `-mregparmcall' means,
     this loop will eventually cause a stack overflow and corrupt the data
     area.  */
  for (i = 0; i < 10000; ++i)
    {
      if ((unsigned) lseek (fd, (off_t) 1000, SEEK_CUR) != (i + 1) * 1000)
	abort ();
    }

  close (fd);
  return 0;
}

/* inc (.) should not pop one shortword: */
/* { dg-final { scan-assembler-not "ret\[ \\t\]\\\$2" } } */

/* main (...) should adjust the stack after calling open (...), a variadic
   function: */
/* { dg-final { scan-assembler "addw\[ \\t\]\\\$4,\[ \\t\]%sp" } } */

/* main (...) should not adjust the stack after calling __umoddi3 (...) or
   lseek (...): */
/* { dg-final { scan-assembler-not "addw\[ \\t\]\\\$\[\^4\].*,\[ \\t\]%sp" } } */
