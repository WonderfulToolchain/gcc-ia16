/* { dg-do compile } */

#ifdef __ia16__
#define SHIFT 13
#else
#define SHIFT 29
#endif

typedef int v4si __attribute__ ((vector_size (1 << SHIFT)));
