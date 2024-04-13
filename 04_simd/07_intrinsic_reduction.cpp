#include <cstdio>
#include <x86intrin.h>

int main() {
  const int N = 16;
  float a[N];
  for (int i=0; i<N; i++)
    a[i] = 1;
  __m512 avec = _mm512_load_ps(a);
  a[0] = _mm512_reduce_add_ps(avec);
  printf("%g\n",a[0]);
}
