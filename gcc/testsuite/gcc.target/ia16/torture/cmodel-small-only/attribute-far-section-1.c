/* { dg-do run } */
/* { dg-options "--std=gnu11 -Wall --save-temps" } */

/* Check that far_section -> near function calls work correctly.  */

int printf (const char *, ...);
int puts (const char *);
int rand (void);

__attribute__ ((noinline, far_section))
__far int hello (const char *thang1, const char *thang2)
{
  printf ("Hello %s%s %d\n", thang1, thang2, rand ());
  puts ("w00t!");
  return 0;
}

char world[] = "world";
char mark[] = "!";

int main (void)
{
  return hello (world, mark);
}
