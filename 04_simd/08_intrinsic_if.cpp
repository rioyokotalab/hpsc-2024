#include <cstdio>
#include <x86intrin.h>

int main() {
  const int N = 16;
  float a[N], b[N];
  for (int i=0; i<N; i++)
    a[i] = i;
  __m512 avec = _mm512_load_ps(a);
  __m512 bvec = _mm512_setzero_ps();
  __m512 three = _mm512_set1_ps(3);
  __mmask16 mask = _mm512_cmp_ps_mask(avec, three, _MM_CMPINT_GT);
  bvec = _mm512_mask_blend_ps(mask, bvec, avec);
  _mm512_store_ps(b, bvec);
  for(int i=0; i<N; i++)
    printf("%d %g\n",i,b[i]);
}
