/* PR target/100305 */

typedef double v2df __attribute__((vector_size(16)));

#ifdef __ia16__
#define N 1024
#else
#define N 4096
#endif
void consume (void *);
v2df
foo (void)
{
  double x[N+2];
  consume (x);
  return (v2df) { x[N], x[N + 1] };
}
