#include "hip/hip_runtime.h"
#include <cstdio>

__global__ void thread(float *a) {
  a[threadIdx.x] = threadIdx.x;
}

int main(void) {
  const int N = 4;
  float *a;
  hipMallocManaged(&a, N*sizeof(float));
  hipLaunchKernelGGL(thread, dim3(1), dim3(N), 0, 0, a);
  hipDeviceSynchronize();
  for (int i=0; i<N; i++)
    printf("%d %g\n",i,a[i]);
  hipFree(a);
}