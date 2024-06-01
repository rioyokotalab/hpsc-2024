#include <cstdlib>
#include <cstring>
#include <cmath>

#define NX 41
#define NY 41
#define NT 500
#define NIT 50
#define DX (2 / (NX - 1))
#define DY (2 / (NY - 1))
#define DT 0.01
#define RHO 1
#define NU 0.02

#define FROM(x, y) (from * NX * NY + y * NX + x)
#define TO(x, y) (to * NX * NY + y * NX + x)
#define Ix(x, y) (y * NX + x)

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
  int from = 0, to = 1 - from;
  for (int n = 0; n < NT; n++)
  {
    for (int j = 1; j < NY - 1; j++)
    {
      for (int i = 1; i < NX - 1; i++)
      {
        // b[j,i]
        b[Ix(i, j)] = RHO * (1 / DT *
                                 ((u[FROM(i + 1, j)] - u[FROM(i - 1, j)]) / (2 * DX) + (v[FROM(i, j + 1)] - v[FROM(i, j - 1)]) / (2 * DY)) -
                             powf((u[FROM(i + 1, j)] - u[FROM(i - 1, j)]) / (2 * DX), 2) - 2 * ((u[FROM(i, j + 1)] - u[FROM(i, j - 1)]) / (2 * DY) * (v[FROM(i + 1, j)] - v[FROM(i - 1, j)]) / (2 * DX)) -
                             powf((v[FROM(i, j + 1)] - v[FROM(i, j - 1)]) / (2 * DY), 2));
      }
    }

    for (int it = 0; it < NIT; it++)
    {
      for (int j = 1; j < NY - 1; j++)
      {
        for (int i = 1; i < NX - 1; i++)
        {
          // p[j,i]
          p[TO(i, j)] = (powf(DY, 2) * (p[FROM(i + 1, j)] + p[FROM(i - 1, j)]) +
                         powf(DX, 2) * (p[FROM(i, j + 1)] + p[FROM(i, j - 1)]) -
                         b[Ix(i, j)] * powf(DX, 2) * powf(DY, 2)) /
                        (2 * (powf(DX, 2) + powf(DY, 2)));
        }
      }
    }

    for (int j = 1; j < NY - 1; j++)
    {
      for (int i = 1; i < NX - 1; i++)
      {
        // u[j,i]

        // v[j,i]
      }
    }

    from = 1 - from;
    to = 1 - to;
  }
}