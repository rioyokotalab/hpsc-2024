#include <cstdio>
#include <cstdlib>
#include <cooperative_groups.h>
using namespace cooperative_groups;

__global__ void scan(int *a, int *b, int N) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  grid_group grid = this_grid();
  for(int j=1; j<N; j<<=1) {
    b[i] = a[i];
    grid.sync();
    a[i] += b[i-j];
    grid.sync();
  }
}

int main() {
  const int N=8;
  int *a, *b;
  cudaMallocManaged(&a, N*sizeof(int));
  cudaMallocManaged(&b, N*sizeof(int));
  for(int i=0; i<N; i++) {
    a[i] = rand() & 3;
    printf("%*d ",2,a[i]);
  }
  printf("\n");
  void *args[] = {(void *)&a,  (void *)&b, (void *)&N};
  cudaLaunchCooperativeKernel((void*)scan, 2, N/2, args);
  cudaDeviceSynchronize();
  for(int i=0; i<N; i++)
    printf("%*d ",2,a[i]);
  printf("\n");
  cudaFree(a);
  cudaFree(b);
}
