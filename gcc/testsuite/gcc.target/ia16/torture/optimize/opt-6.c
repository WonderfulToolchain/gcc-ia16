/* { dg-do run } */
/* { dg-options "-std=gnu11 --save-temps" } */

/* Test that GCC does not produce erroneous code for 3-way comparisons
   against zero.

   This issue was reported by MFLD --- https://github.com/tkchia/gcc-ia16/
   issues/40.  The code for this test case was mostly lifted from /bin/cat
   for ELKS, by MTK et al. --- https://github.com/jbruchon/elks/blob/master/
   elkscmd/file_utils/cat.c.  */

#include <stdio.h>
#include <stdlib.h>

#define CAT_BUF_SIZE 4096

static char readbuf[CAT_BUF_SIZE];

__attribute__((noinline))
static int fake_read(int fd, char *buf, size_t n)
{
	int rv;
	__asm volatile ("# read" : "=r" (rv)
				 : "0" ((int)0), "r" (fd), "r" (buf), "r" (n)
				 : "memory", "cc");
	return 0;
}

__attribute__((noinline))
static int fake_write(int fd, const char *buf, size_t n)
{
	int rv;
	__asm volatile ("# write" : "=r" (rv)
				  : "0" ((int)0), "r" (fd), "r" (buf), "r" (n)
				  : "memory", "cc");
	return 0;
}

static int dumpfile(int fd)
{
	int nred;

	while ((nred = fake_read(fd, readbuf, CAT_BUF_SIZE)) > 0) {
		fake_write(1, readbuf, nred);
	}
	if (nred < 0) return -1;
	return 0;
}

int main(int argc, char **argv)
{
	return dumpfile(0);
}
