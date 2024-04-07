#include <iostream>
#include <typeinfo>
#include <random>
#include <stdint.h>
#include <cublas_v2.h>
#include <chrono>
using namespace std;

__global__ void kernel(int dim_m, int dim_n, int dim_k,
		       float *d_a, float *d_b, float *d_c) {
  int offset_a_m = 64 * blockIdx.x;
  int offset_b_n = 64 * blockIdx.y;
  int i = threadIdx.x;

  __shared__ float block_a[8][64];
  __shared__ float block_b[8][64];
  float block_c[8][8];

  for (int m = 0; m < 8; ++m)
    for (int n = 0; n < 8; ++n)
      block_c[m][n] = 0;

  int offset_n = threadIdx.x / 8 * 8;
  int offset_m = threadIdx.x % 8 * 8;
  for (int k = 0; k < dim_k; k += 8) {
    int offset_a_k = k, offset_b_k = k;
    __syncthreads();
    for (int j = 0; j < 8; ++j) {
      block_a[j][i] = d_a[(offset_a_k + j) * dim_m + offset_a_m + i];
      block_b[j][i] = d_b[(offset_b_n + i) * dim_k + offset_b_k + j];
    }
    __syncthreads();
#pragma unroll
    for (int j = 0; j < 8; ++j) {
      for (int m = 0; m < 8; ++m) {
	for (int n = 0; n < 8; ++n) {
	  block_c[m][n] += block_a[j][offset_m + m] * block_b[j][offset_n + n];
	}
      }
    }
  }
  for (int m = 0; m < 8; ++m) {
    for (int n = 0; n < 8; ++n) {
      int c_n = offset_b_n + offset_n + n;
      int c_m = offset_a_m + offset_m + m;
      if (c_n < dim_n && c_m < dim_m) {
	d_c[c_n * dim_m + c_m] = block_c[m][n];
      }
    }
  }
}

int main(int argc, const char **argv) {
  int m = 10240;
  int k = 4096;
  int n = 8192;
  float alpha = 1.0;
  float beta = 0.0;
  int Nt = 10;
  float *A, *B, *C, *C2;
  cudaMallocManaged(&A, m * k * sizeof(float));
  cudaMallocManaged(&B, k * n * sizeof(float));
  cudaMallocManaged(&C, m * n * sizeof(float));
  cudaMallocManaged(&C2, m * n * sizeof(float));
  for (int i=0; i<m; i++)
    for (int j=0; j<k; j++)
      A[k*i+j] = drand48();
  for (int i=0; i<k; i++)
    for (int j=0; j<n; j++)
      B[n*i+j] = drand48();
  for (int i=0; i<n; i++)
    for (int j=0; j<m; j++)
      C[m*i+j] = C2[m*i+j] = 0;
  cublasHandle_t cublas_handle;
  cublasCreate(&cublas_handle);
  auto tic = chrono::steady_clock::now();
  for (int i = 0; i < Nt+2; i++) {
    if (i == 2) tic = chrono::steady_clock::now();
    cublasSgemm(cublas_handle,
		CUBLAS_OP_N,
		CUBLAS_OP_N,
		m,
		n,
		k,
		&alpha,
		A,
		m,
		B,
		k,
		&beta,
		C,
		m);
    cudaDeviceSynchronize();
  }
  auto toc = chrono::steady_clock::now();
  int64_t num_flops = (2 * int64_t(m) * int64_t(n) * int64_t(k)) + (2 * int64_t(m) * int64_t(n));
  double tcublas = chrono::duration<double>(toc - tic).count() / Nt;
  double cublas_flops = double(num_flops) / tcublas / 1.0e9;
  int tile = 64;
  dim3 block = dim3(tile);
  dim3 grid = dim3((m+tile-1)/tile, (n+tile-1)/tile);
  for (int i = 0; i < Nt+2; i++) {
    if (i == 2) tic = chrono::steady_clock::now();
    kernel<<< grid, block >>>(m,
			      n,
			      k,
			      A,
			      B,
			      C2);
    cudaDeviceSynchronize();
  }
  toc = chrono::steady_clock::now();
  double tcutlass = chrono::duration<double>(toc - tic).count() / Nt;
  double cutlass_flops = double(num_flops) / tcutlass / 1.0e9;
  printf("CUBLAS: %.2f Gflops, CUTLASS: %.2f Gflops\n", cublas_flops, cutlass_flops);
  double err = 0;
  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
      err += fabs(C[m*i+j] - C2[m*i+j]);
    }
  }
  printf("error: %lf\n", err/n/m);
  cudaFree(A);
  cudaFree(B);
  cudaFree(C);
  cudaFree(C2);
  cublasDestroy(cublas_handle);
}
