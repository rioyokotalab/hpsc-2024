#include <cstdio>

__device__ __managed__ int sum;

__device__ int warpSum(int a) {
  for (int offset=16; offset>0; offset >>= 1)
    a += __shfl_down_sync(0xffffffff, a, offset);
  return a;
}

__global__ void reduction(int &sum, int *a) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  int b = warpSum(a[i]);
  if ((threadIdx.x & 31) == 0)
    atomicAdd(&sum, b);
}

int main(void) {
  const int N = 128;
  const int M = 64;
  int *a;
  cudaMallocManaged(&a, N*sizeof(int));
  for (int i=0; i<N; i++) a[i] = 1;
  reduction<<<N/M,M>>>(sum, a);
  cudaDeviceSynchronize();
  printf("%d\n",sum);
  cudaFree(a);
}
