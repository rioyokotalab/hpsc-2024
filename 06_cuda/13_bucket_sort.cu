#include <cstdio>
#include <cstdlib>

__global__ void bucket_sort(int *bucket, int *key, int range)
{
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  atomicAdd(&bucket[key[i]], 1);
  __syncthreads();
  for (int i = 0, j = 0; i < range; i++)
  {
    for (; bucket[i] > 0; bucket[i]--)
    {
      key[j++] = i;
    }
  }
}

int main()
{
  int n = 50;
  int range = 5;
  // std::vector<int> key(n);
  int *key, *bucket;
  cudaMallocManaged(&bucket, range * sizeof(int));
  cudaMallocManaged(&key, n * sizeof(int));
  for (int i = 0; i < n; i++)
  {
    key[i] = rand() % range;
    printf("%d ", key[i]);
  }
  printf("\n");

  /*std::vector<int> bucket(range);
  for (int i=0; i<range; i++) {
    bucket[i] = 0;
  }
  for (int i=0; i<n; i++) {
    bucket[key[i]]++;
  }
  for (int i=0, j=0; i<range; i++) {
    for (; bucket[i]>0; bucket[i]--) {
      key[j++] = i;
    }
  }*/
  for (int i = 0; i < range; i++)
  {
    bucket[i] = 0;
  }
  bucket_sort<<<1, n>>>(bucket, key, range);
  cudaDeviceSynchronize();

  for (int i = 0; i < n; i++)
  {
    printf("%d ", key[i]);
  }
  printf("\n");
  cudaFree(bucket);
  cudaFree(key);
}
