#if defined (STACK_SIZE) && STACK_SIZE <= 50000
#define LARGE 100
#define SMALL 50
#define SMALL8 40
#define SMALL6 30
#define SMALL4 20
#else
#define LARGE 200
#define SMALL 100
#define SMALL8 80
#define SMALL6 60
#define SMALL4 40
#endif


int toto()
{
  int i, j, k;
  int a[SMALL][LARGE];
  int b[SMALL];

  for (i = 1; i < SMALL; i++)
    {
      for (j = 1; j < SMALL8; j++)
	a[j][i] = a[j+1][2*i-1*j] + 12;

      b[i] = b[i-1] + 10;

      for (j = 1; j < SMALL6; j++)
	a[j][i] = a[j+1][i-1] + 8;

      if (i == 23)
	b[i] = a[i-1][i] + 6;

      for (j = 1; j < SMALL4; j++)
	a[j][i] = a[j+1][i-1] + 4;
    }

  return a[3][5] + b[1];
}

/* { dg-final { scan-tree-dump-times "number of SCoPs: 1" 1 "graphite"} } */
