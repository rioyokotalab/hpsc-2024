#include <cstdio>

__global__ void oddeven(float *a) {
  int i = threadIdx.x;
  if (i & 1)
    a[i] = -i;
  else
    a[i] = i;
}

int main(void) {
  const int N = 32;
  float *a;
  cudaMallocManaged(&a, N*sizeof(float));
  oddeven<<<1,N>>>(a);
  cudaDeviceSynchronize();
  for (int i=0; i<N; i++)
    printf("%d %g\n",i,a[i]);
  cudaFree(a);
}