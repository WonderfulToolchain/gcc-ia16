/* { dg-options "-masm=intel -std=gnu11 -fno-inline --save-temps" } */
/* { dg-do run } */

/* Test that using Intel assembly language syntax does not result in incorrect
   code or other badness.  */

int strcmp (const char *, const char *);
int puts (const char *);
void abort (void);

#ifdef __IA16_CMODEL_TINY__
static volatile const char crud[] =
#else
static volatile const char __far crud[] =
#endif
  {
    'H',
    'H' ^ 'e',
    'H' ^ 'e' ^ 'l',
    'H' ^ 'e' ^ 'l' ^ 'l',
    'H' ^ 'e' ^ 'l' ^ 'l' ^ 'o',
    'H' ^ 'e' ^ 'l' ^ 'l' ^ 'o' ^ ' ',
    'H' ^ 'e' ^ 'l' ^ 'l' ^ 'o' ^ ' ' ^ 'w',
    'H' ^ 'e' ^ 'l' ^ 'l' ^ 'o' ^ ' ' ^ 'w' ^ 'o',
    'H' ^ 'e' ^ 'l' ^ 'l' ^ 'o' ^ ' ' ^ 'w' ^ 'o' ^ 'r',
    'H' ^ 'e' ^ 'l' ^ 'l' ^ 'o' ^ ' ' ^ 'w' ^ 'o' ^ 'r' ^ 'l',
    'H' ^ 'e' ^ 'l' ^ 'l' ^ 'o' ^ ' ' ^ 'w' ^ 'o' ^ 'r' ^ 'l' ^ 'd',
    'H' ^ 'e' ^ 'l' ^ 'l' ^ 'o' ^ ' ' ^ 'w' ^ 'o' ^ 'r' ^ 'l' ^ 'd' ^ 0,
  };

int
main (void)
{
  static char msg[sizeof crud];
  unsigned i = 0;
  char x, y = 0, t;

  do
    {
      t = crud[i];
      x = t ^ y;
      y = t;
      msg[i++] = x;
    }
  while (x != 0);

  if (i != sizeof crud)
    abort ();

  if (strcmp ("Hello world", msg) != 0)
    abort ();

  puts (msg);
  return 0;
}
