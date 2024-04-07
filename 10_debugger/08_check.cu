#include <cstdio>

void cudaCheckError() {
  cudaError_t err=cudaGetLastError();
  if(err!=cudaSuccess) {
    fprintf(stderr,"CUDA failure %s:%d: '%s'\n",__FILE__,__LINE__,cudaGetErrorString(err));
    exit(-1);
  }
}

__global__ void thread(float *a) {
  a[threadIdx.x] = threadIdx.x;
}

int main(void) {
  const int N = 2048;
  float *a;
  cudaMallocManaged(&a, N*sizeof(float));
  thread<<<1,N>>>(a);
  cudaCheckError();
  for (int i=0; i<N; i++)
    printf("%d %g\n",i,a[i]);
  cudaFree(a);
}
