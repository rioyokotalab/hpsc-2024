#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <chrono>
using namespace std;

extern "C" void sgemm_(char*, char*, int*, int*, int*, float*, float*, int*, float*, int*, float*, float*, int*);

int main() {
  int N = 8192;
  vector<float> A(N*N);
  vector<float> B(N*N);
  vector<float> C(N*N);
  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      A[N*i+j] = drand48();
      B[N*i+j] = drand48();
      C[N*i+j] = 0;
    }
  }
  float alpha = 1.0;
  float beta = 0.0;
  char T = 'N';
  sgemm_(&T, &T, &N, &N, &N, &alpha, &B[0], &N, &A[0], &N, &beta, &C[0], &N);
  auto tic = chrono::steady_clock::now();
  sgemm_(&T, &T, &N, &N, &N, &alpha, &B[0], &N, &A[0], &N, &beta, &C[0], &N);
  auto toc = chrono::steady_clock::now();
  double time = chrono::duration<double>(toc - tic).count();
  printf("N=%d: %lf s (%lf GFlops)\n",N,time,2.*N*N*N/time/1e9);
}
