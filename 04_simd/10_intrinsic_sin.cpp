#include <cstdio>
#include <cmath>
#include <immintrin.h>

int main() {
  const int N = 8;
  float x[N], y[N];
  for(int i=0; i<N; i++)
    x[i] = i * M_PI / (N - 1);
  __m256 xvec = _mm256_load_ps(x);
  xvec = _mm256_sin_ps(xvec);
  _mm256_store_ps(y, xvec);
  for(int i=0; i<N; i++)
    printf("%g %g\n",x[i],y[i]);
}
