#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>

#define NX 41
#define NY 41
#define NT 500
#define NIT 50
#define DX (2.0 / (NX - 1))
#define DY (2.0 / (NY - 1))
#define DT 0.01
#define RHO 1.0
#define NU 0.02

#define FROM(x, y) (from * NX * NY + (y) * NX + (x))
#define TO(x, y) (to * NX * NY + (y) * NX + (x))
#define Ix(x, y) ((y) * NX + (x))
#define FROM_(x, y) (from_ * NX * NY + (y) * NX + (x))
#define TO_(x, y) (to_ * NX * NY + (y) * NX + (x))

float *array(size_t size)
{
  float *array = (float *)malloc(sizeof(float) * size);
  memset(array, 0, size);
  return array;
}

int main()
{
  float *u, *v, *p, *b;
  u = array(2 * NX * NY);
  v = array(2 * NX * NY);
  p = array(2 * NX * NY);
  b = array(NX * NY);
  int from = 0, to = 1;
  int from_ = 0, to_ = 1;

  FILE *ufile = fopen("u.dat", "w");
  FILE *vfile = fopen("v.dat", "w");
  FILE *pfile = fopen("p.dat", "w");

  for (int n = 0; n < NT; n++)
  {
    from = 1 - from;
    to = 1 - to;

    for (int j = 1; j < NY - 1; j++)
    {
      for (int i = 1; i < NX - 1; i++)
      {
        // b[j,i]
        b[Ix(i, j)] = RHO * (1.0 / DT *
                                 ((u[FROM(i + 1, j)] - u[FROM(i - 1, j)]) / (2 * DX) + (v[FROM(i, j + 1)] - v[FROM(i, j - 1)]) / (2 * DY)) -
                             powf((u[FROM(i + 1, j)] - u[FROM(i - 1, j)]) / (2 * DX), 2) -
                             2 * ((u[FROM(i, j + 1)] - u[FROM(i, j - 1)]) / (2 * DY) * (v[FROM(i + 1, j)] - v[FROM(i - 1, j)]) / (2 * DX)) -
                             powf((v[FROM(i, j + 1)] - v[FROM(i, j - 1)]) / (2 * DY), 2));
      }
    }
    for (int it = 0; it < NIT; it++)
    {
      from_ = 1 - from_;
      to_ = 1 - to_;

      for (int j = 1; j < NY - 1; j++)
      {
        for (int i = 1; i < NX - 1; i++)
        {
          // p[j,i]
          p[TO_(i, j)] = (powf(DY, 2) * (p[FROM_(i + 1, j)] + p[FROM_(i - 1, j)]) +
                          powf(DX, 2) * (p[FROM_(i, j + 1)] + p[FROM_(i, j - 1)]) -
                          b[Ix(i, j)] * powf(DX, 2) * powf(DY, 2)) /
                         (2 * (powf(DX, 2) + powf(DY, 2)));
        }
      }

      for (int i = 0; i < NY; i++)
      {
        p[TO_(0, i)] = p[TO_(1, i)];
        p[TO_(NX - 1, i)] = p[TO_(NX - 2, i)];
      }
      for (int i = 0; i < NX; i++)
      {
        p[TO_(i, 0)] = p[TO_(i, 1)];
        p[TO_(i, NY - 1)] = p[TO_(i, NY - 2)];
      }
    }

    for (int j = 1; j < NY - 1; j++)
    {
      for (int i = 1; i < NX - 1; i++)
      {
        // u[j,i]
        u[TO(i, j)] = u[FROM(i, j)] - u[FROM(i, j)] * DT / DX * (u[FROM(i, j)] - u[FROM(i - 1, j)]) - v[FROM(i, j)] * DT / DY * (u[FROM(i, j)] - u[FROM(i, j - 1)]) -
                      DT / (2 * RHO * DX) * (p[TO_(i + 1, j)] - p[TO_(i - 1, j)]) + NU * DT / powf(DX, 2) * (u[FROM(i + 1, j)] - 2 * u[FROM(i, j)] + u[FROM(i - 1, j)]) +
                      NU * DT / powf(DY, 2) * (u[FROM(i, j + 1)] - 2 * u[FROM(i, j)] + u[FROM(i, j - 1)]);

        // v[j,i]
        v[TO(i, j)] = v[FROM(i, j)] - u[FROM(i, j)] * DT / DX * (v[FROM(i, j)] - v[FROM(i - 1, j)]) - v[FROM(i, j)] * DT / DY * (v[FROM(i, j)] - v[FROM(i, j - 1)]) -
                      DT / (2 * RHO * DY) * (p[TO_(i, j + 1)] - p[TO_(i, j - 1)]) + NU * DT / powf(DX, 2) * (v[FROM(i + 1, j)] - 2 * v[FROM(i, j)] + v[FROM(i - 1, j)]) +
                      NU * DT / powf(DY, 2) * (v[FROM(i, j + 1)] - 2 * v[FROM(i, j)] + v[FROM(i, j - 1)]);
      }
    }

    for (int i = 0; i < NX; i++)
    {
      u[TO(i, 0)] = 0;
      u[TO(i, NY - 1)] = 1.0;
      v[TO(i, 0)] = v[TO(i, NY - 1)] = 0;
    }
    for (int i = 0; i < NY; i++)
    {
      u[TO(0, i)] = u[TO(NX - 1, i)] = 0;
      v[TO(0, i)] = v[TO(NX - 1, i)] = 0;
    }

    for (int j = 0; j < NY; j++)
    {
      for (int i = 0; i < NX; i++)
      {
        fprintf(ufile, "%f ", u[TO(i, j)]);
      }
    }
    fprintf(ufile, "\n");
    for (int j = 0; j < NY; j++)
    {
      for (int i = 0; i < NX; i++)
      {
        fprintf(vfile, "%f ", v[TO(i, j)]);
      }
    }
    fprintf(vfile, "\n");
    for (int j = 0; j < NY; j++)
    {
      for (int i = 0; i < NX; i++)
      {
        fprintf(pfile, "%f ", p[TO_(i, j)]);
      }
    }
    fprintf(pfile, "\n");
  }
  fclose(ufile);
  fclose(vfile);
  fclose(pfile);

  return 0;
}