#include <cstdio>
#include <immintrin.h>

int main() {
  const int N = 8;
  float a[N], b[N], c[N];
  for(int i=0; i<N; i++) {
    a[i] = i;
    b[i] = i * 0.1;
    c[i] = 0;
  }
  __m256 avec = _mm256_load_ps(a);
  __m256 bvec = _mm256_load_ps(b);
  __m256 cvec = _mm256_add_ps(avec, bvec);
  _mm256_store_ps(c, cvec);
  for(int i=0; i<N; i++)
    printf("%d %g\n",i,c[i]);
}
