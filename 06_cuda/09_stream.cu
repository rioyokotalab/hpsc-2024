#include <cstdio>

__global__ void block(float *a, int N) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if(i>=N) return;
  a[i] = i;
}

int main(void) {
  const int N = 2000;
  const int M = 1024;
  const int num_streams = 8;
  float *a;
  cudaStream_t streams[num_streams];
  cudaMallocManaged(&a, N*sizeof(float));
  for (int i=0; i<num_streams; i++) {
    cudaStreamCreate(&streams[i]);
    block<<<(N+M-1)/M,M,0,streams[i]>>>(a,N);
  }
  cudaDeviceSynchronize();
  for (int i=0; i<N; i++)
    printf("%d %g\n",i,a[i]);
  cudaFree(a);
}
