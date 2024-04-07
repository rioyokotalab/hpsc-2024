#include <cstdlib>
#include <cstdio>
#include <vector>
#include <chrono>
using namespace std;

void matmult(float *A, float *B, float *C, int N) {
#pragma acc kernels loop gang, vector(32) independent
  for (int i=0; i<N; i++)
#pragma acc loop gang, vector(32) independent
    for (int j=0; j<N; j++) {
      float Cij = 0;
#pragma acc loop reduction(+:Cij)
      for (int k=0; k<N; k++)
        Cij += A[N*i+k] * B[N*k+j];
      C[N*i+j] = Cij;
    }
}

int main() {
  const int N = 2048;
  float *A = new float [N*N];
  float *B = new float [N*N];
  float *C = new float [N*N];
  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      A[N*i+j] = drand48();
      B[N*i+j] = drand48();
      C[N*i+j] = 0;
    }
  }
  matmult(A,B,C,N);
  auto tic = chrono::steady_clock::now();
  matmult(A,B,C,N);
  auto toc = chrono::steady_clock::now();
  double time = chrono::duration<double>(toc - tic).count();
  printf("N=%d: %lf s (%lf GFlops)\n",N,time,2.*N*N*N/time/1e9);
  delete[] A;
  delete[] B;
  delete[] C;
}
