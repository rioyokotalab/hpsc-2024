#include <stdio.h>

#define NX 41
#define NY 41
#define NT 500
#define NIT 50
#define DX (2.0 / (NX - 1))
#define DY (2.0 / (NY - 1))
#define DT 0.01
#define RHO 1.0
#define NU 0.02

#define BS 32

#define Ix(x, y) ((y) * NX + (x))

__global__ void init(float *p, float *u, float *v)
{
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  int j = blockIdx.y * blockDim.y + threadIdx.y;
  p[Ix(i, j)] = 0;
  p[NX * NY + Ix(i, j)] = 0;
  u[Ix(i, j)] = 0;
  u[NX * NY + Ix(i, j)] = 0;
  v[Ix(i, j)] = 0;
  v[NX * NY + Ix(i, j)] = 0;
}

__global__ void step(float *p, float *u, float *v)
{
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  int j = blockIdx.y * blockDim.y + threadIdx.y;
  float *pn = p + NY * NX;
  float *un = u + NY * NX;
  float *vn = v + NY * NX;
  
  if (i >= NX || j >= NY)
  {
    return;
  }

  float b = RHO * (1.0 / DT *
                       ((u[Ix(i + 1, j)] - u[Ix(i - 1, j)]) / (2 * DX) + (v[Ix(i, j + 1)] - v[Ix(i, j - 1)]) / (2 * DY)) -
                   powf((u[Ix(i + 1, j)] - u[Ix(i - 1, j)]) / (2 * DX), 2) -
                   2 * ((u[Ix(i, j + 1)] - u[Ix(i, j - 1)]) / (2 * DY) * (v[Ix(i + 1, j)] - v[Ix(i - 1, j)]) / (2 * DX)) -
                   powf((v[Ix(i, j + 1)] - v[Ix(i, j - 1)]) / (2 * DY), 2));

  // p
  for (int it = 0; it < NIT; it++)
  {
    pn[Ix(i, j)] = p[Ix(i, j)];

    __syncthreads();

    p[Ix(i, j)] = (powf(DY, 2) * (pn[Ix(i + 1, j)] + pn[Ix(i - 1, j)]) +
                   powf(DX, 2) * (pn[Ix(i, j + 1)] + pn[Ix(i, j - 1)]) -
                   b * powf(DX, 2) * powf(DY, 2)) /
                  (2 * (powf(DX, 2) + powf(DY, 2)));

    __syncthreads();
    if (j == 0)
    {
      p[Ix(i, 0)] = p[Ix(i, 1)];
    }
    else if (j == NY - 1)
    {
      p[Ix(i, NY - 1)] = p[Ix(i, NY - 2)];
    }
    else if (i == 0)
    {
      p[Ix(0, j)] = p[Ix(1, j)];
    }
    else if (i == NX - 1)
    {
      p[Ix(NX - 1, j)] = p[Ix(NX - 2, j)];
    }
  }

  // u,v
  un[Ix(i, j)] = u[Ix(i, j)];
  vn[Ix(i, j)] = v[Ix(i, j)];
  __syncthreads();
  if (j == 0)
  {
    u[Ix(i, 0)] = 0;
    v[Ix(i, 0)] = 0;
  }
  else if (j == NY - 1)
  {
    u[Ix(i, NY - 1)] = 1;
    v[Ix(i, NY - 1)] = 0;
  }
  else if (i == 0)
  {
    u[Ix(0, j)] = 0;
    v[Ix(0, j)] = 0;
  }
  else if (i == NX - 1)
  {
    u[Ix(NX - 1, j)] = 0;
    v[Ix(NX - 1, j)] = 0;
  }
  else
  {
    u[Ix(i, j)] = un[Ix(i, j)] - un[Ix(i, j)] * DT / DX * (un[Ix(i, j)] - un[Ix(i - 1, j)]) - vn[Ix(i, j)] * DT / DY * (un[Ix(i, j)] - un[Ix(i, j - 1)]) -
                  DT / (2 * RHO * DX) * (p[Ix(i + 1, j)] - p[Ix(i - 1, j)]) + NU * DT / powf(DX, 2) * (un[Ix(i + 1, j)] - 2 * un[Ix(i, j)] + un[Ix(i - 1, j)]) +
                  NU * DT / powf(DY, 2) * (un[Ix(i, j + 1)] - 2 * un[Ix(i, j)] + un[Ix(i, j - 1)]);

    v[Ix(i, j)] = vn[Ix(i, j)] - un[Ix(i, j)] * DT / DX * (vn[Ix(i, j)] - vn[Ix(i - 1, j)]) - vn[Ix(i, j)] * DT / DY * (vn[Ix(i, j)] - vn[Ix(i, j - 1)]) -
                  DT / (2 * RHO * DY) * (p[Ix(i, j + 1)] - p[Ix(i, j - 1)]) + NU * DT / powf(DX, 2) * (vn[Ix(i + 1, j)] - 2 * vn[Ix(i, j)] + vn[Ix(i - 1, j)]) +
                  NU * DT / powf(DY, 2) * (vn[Ix(i, j + 1)] - 2 * vn[Ix(i, j)] + vn[Ix(i, j - 1)]);
  }
}

int main()
{
  float *u, *v, *p;
  cudaMallocManaged(&p, 2 * NX * NY * sizeof(float));
  cudaMallocManaged(&u, 2 * NX * NY * sizeof(float));
  cudaMallocManaged(&v, 2 * NX * NY * sizeof(float));
  init<<<dim3((NX + BS - 1) / BS, (NY + BS - 1) / BS, 1), dim3(BS, BS, 1)>>>(p, u, v);

  FILE *ufile = fopen("u.dat", "w");
  FILE *vfile = fopen("v.dat", "w");
  FILE *pfile = fopen("p.dat", "w");

  for (int n = 0; n < NT; n++)
  {

    step<<<dim3((NX + BS - 1) / BS, (NY + BS - 1) / BS, 1), dim3(BS, BS, 1)>>>(p, u, v);
    cudaDeviceSynchronize();

    for (int j = 0; j < NY; j++)
    {
      for (int i = 0; i < NX; i++)
      {
        fprintf(ufile, "%f ", u[Ix(i, j)]);
      }
    }
    fprintf(ufile, "\n");
    for (int j = 0; j < NY; j++)
    {
      for (int i = 0; i < NX; i++)
      {
        fprintf(vfile, "%f ", v[Ix(i, j)]);
      }
    }
    fprintf(vfile, "\n");
    for (int j = 0; j < NY; j++)
    {
      for (int i = 0; i < NX; i++)
      {
        fprintf(pfile, "%f ", p[Ix(i, j)]);
      }
    }
    fprintf(pfile, "\n");
  }
  fclose(ufile);
  fclose(vfile);
  fclose(pfile);

  return 0;
}
