#include <cstdio>
#include <x86intrin.h>

int main() {
  const int N = 16;
  float a[N], b[N], c[N];
  for(int i=0; i<N; i++) {
    a[i] = i;
    b[i] = i * 0.01;
    c[i] = 0;
  }
  __m512 avec = _mm512_load_ps(a);
  __m512 bvec = _mm512_load_ps(b);
  __m512 cvec = _mm512_add_ps(avec, bvec);
  _mm512_store_ps(c, cvec);
  for(int i=0; i<N; i++)
    printf("%d %g\n",i,c[i]);
}
