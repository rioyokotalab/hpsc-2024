#include <cstdio>
#include <immintrin.h>

int main() {
  const int N = 8;
  int idx[N] = {3,7,0,6,2,5,1,4};
  float a[N], b[N];
  for(int i=0; i<N; i++)
    a[idx[i]] = i * 0.1;
  __m256i ivec = _mm256_load_si256((__m256i*)idx);
  __m256 avec = _mm256_load_ps(a);
  avec = _mm256_permutevar8x32_ps(avec, ivec);
  _mm256_store_ps(b, avec);
  for(int i=0; i<N; i++)
    printf("%d %3.1f %3.1f\n",i,a[i],b[i]);
}
