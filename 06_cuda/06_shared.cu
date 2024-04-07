#include <cstdio>

__device__ __managed__ int sum;

__global__ void reduction(int &sum, int *a) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  extern __shared__ int b[];
  __syncthreads();
  b[threadIdx.x] = a[i];
  __syncthreads();
  int c = 0;
  for (int j=0; j<blockDim.x; j++)
    c += b[j];
  if (threadIdx.x == 0)
    atomicAdd(&sum, c);
}

int main(void) {
  const int N = 128;
  const int M = 64;
  int *a;
  cudaMallocManaged(&a, N*sizeof(int));
  for (int i=0; i<N; i++) a[i] = 1;
  reduction<<<N/M,M,M*sizeof(int)>>>(sum, a);
  cudaDeviceSynchronize();
  printf("%d\n",sum);
  cudaFree(a);
}
