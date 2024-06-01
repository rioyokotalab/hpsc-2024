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

#define FROM(x, y) (from * NX * NY + (y) * NX + (x))
#define TO(x, y) (to * NX * NY + (y) * NX + (x))
#define Ix(x, y) ((y) * NX + (x))

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

      for (int i = 0; i < NY; i++)
      {
        p[TO(0, i)] = p[TO(1, i)];
        p[TO(NX - 1, i)] = p[TO(NX - 2, i)];
      }
      for (int i = 0; i < NX; i++)
      {
        p[TO(i, 0)] = p[TO(i, 1)];
        p[TO(i, NY - 1)] = p[TO(i, NY - 2)];
      }
    }

    for (int j = 1; j < NY - 1; j++)
    {
      for (int i = 1; i < NX - 1; i++)
      {
        // u[j,i]
        u[TO(i, j)] = u[FROM(i, j)] - u[FROM(i, j)] * DT / DX * (u[FROM(i, j)] - u[FROM(i - 1, j)]) - u[FROM(i, j)] * DT / DY * (u[FROM(i, j)] - u[FROM(i, j - 1)]) -
                      DT / (2 * RHO * DX) * (p[TO(i + 1, j)] - p[TO(i - 1, j)]) + NU * DT / powf(DX, 2) * (u[FROM(i + 1, j)] - 2 * u[FROM(j, i)] + u[FROM(i - 1, j)]) +
                      NU * DT / powf(DY, 2) * (u[FROM(i, j + 1)] - 2 * u[FROM(i, j)] + u[FROM(i, j - 1)]);

        // v[j,i]
        v[TO(i, j)] = v[FROM(i, j)] - v[FROM(i, j)] * DT / DX * (v[FROM(i, j)] - v[FROM(i - 1, j)]) - v[FROM(i, j)] * DT / DY * (v[FROM(i, j)] - v[FROM(i, j - 1)]) -
                      DT / (2 * RHO * DX) * (p[TO(i, j + 1)] - p[TO(i, j - 1)]) + NU * DT / powf(DX, 2) * (v[FROM(i + 1, j)] - 2 * v[FROM(j, i)] + v[FROM(i - 1, j)]) +
                      NU * DT / powf(DY, 2) * (v[FROM(i, j + 1)] - 2 * v[FROM(i, j)] + v[FROM(i, j - 1)]);
      }
    }

    for (int i = 0; i < NX; i++)
    {
      u[TO(i, 0)] = u[TO(i, NY - 1)] = 0;
      v[TO(i, 0)] = v[TO(i, NY - 1)] = 0;
    }
    for (int i = 0; i < NY; i++)
    {
      u[TO(0, i)] = u[TO(NX - 1, i)] = 0;
      v[TO(0, i)] = v[TO(NX - 1, i)] = 0;
    }

    from = 1 - from;
    to = 1 - to;
  }
}