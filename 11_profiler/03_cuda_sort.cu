#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <curand.h>
#include <cooperative_groups.h>
using namespace cooperative_groups;

__global__ void fillBucket(unsigned *key, unsigned *bucket, int n) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if(i>=n) return;
  atomicAdd(&bucket[key[i]], 1);
}

__global__ void scanBucket(unsigned *bucket, unsigned *offset, unsigned *buffer, int range) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if(i>=range) return;
  grid_group grid = this_grid();
  offset[i] = bucket[i];
  for(int j=1; j<range; j<<=1) {
    buffer[i] = offset[i];
    grid.sync();
    if(i>=j) offset[i] += buffer[i-j];
    grid.sync();
  }
  offset[i] -= bucket[i];
}

__global__ void fillKey(unsigned *key, unsigned *bucket, unsigned *offset, int range) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if(i>=range) return;
  int j = offset[i];
  for (; bucket[i]>0; bucket[i]--)
    key[j++] = i;
}

int main() {
  int n = 100000000;
  int m = 256;
  int range = 100000;
  unsigned *key, *bucket, *offset, *buffer;
  cudaMallocManaged(&key, n*sizeof(unsigned));
  cudaMallocManaged(&bucket, range*sizeof(unsigned));
  cudaMallocManaged(&offset, range*sizeof(unsigned));
  cudaMallocManaged(&buffer, range*sizeof(unsigned));
  for (int i=0; i<n; i++)
    key[i] = rand() % range;
  for (int i=0; i<range; i++)
    bucket[i] = 0;
  fillBucket<<<(n+m-1)/m,m>>>(key, bucket, n);
  void *args[] = {(void *)&bucket,  (void *)&offset, (void *)&buffer, (void*)&range};
  cudaLaunchCooperativeKernel((void*)scanBucket, (range+m-1)/m, m, args);
  fillKey<<<(range+m-1)/m,m>>>(key, bucket, offset, range);
  cudaDeviceSynchronize();
  for (int i=1; i<n; i++)
    assert(key[i] >= key[i-1]);
  cudaFree(key);
  cudaFree(bucket);
  cudaFree(offset);
  cudaFree(buffer);
}
