#include <cstdlib>
#include <cstring>

#define NX 41
#define NY 41
#define NT 500
#define NIT 50
#define DX (2 / (NX - 1))
#define DY (2 / (NY - 1))
#define DT 0.01
#define RHO 1
#define NU 0.02

float *array(size_t size)
{
  float *array = (float *)malloc(size);
  memset(array, 0, size);
  return array;
}

int main()
{
  float *u, *v, *p, *b;
  u = array(sizeof(float) * 2 * NX * NY);
  v = array(sizeof(float) * 2 * NX * NY);
  p = array(sizeof(float) * 2 * NX * NY);
  b = array(sizeof(float) * NX * NY);
  int from=0,to=1-from;
  for (int n = 0; n < NT; n++)
  {
    for (int j = 1; j < NY - 1; j++)
    {
      for (int i = 1; i < NX - 1; i++)
      {
        //b[j,i]
      }
    }

    for (int it = 0; it < NIT; it++)
    {
      for (int j = 1; j < NY - 1; j++)
      {
        for (int i = 1; i < NX - 1; i++)
        {
          //p[j,i]
        }
      }
    }

    for (int j = 1; j < NY - 1; j++)
    {
      for (int i = 1; i < NX - 1; i++)
      {
        //u[j,i]

        //v[j,i]
      }
    }

    from=1-from;
    to=1-to;
  }
}