#include <cstdio>
#include <immintrin.h>

int main() {
  const int N = 8;
  float a[N], b[N];
  for (int i=0; i<N; i++)
    a[i] = i;
  __m256 avec = _mm256_load_ps(a);
  __m256 bvec = _mm256_setzero_ps();
  __m256 three = _mm256_set1_ps(3);
  __m256 mask = _mm256_cmp_ps(avec, three, _CMP_GT_OQ);
  bvec = _mm256_blendv_ps(bvec, avec, mask);
  _mm256_store_ps(b, bvec);
  for(int i=0; i<N; i++)
    printf("%d %g\n",i,b[i]);
}
