#include <cstdio>
#include <x86intrin.h>

int main() {
  const int N = 16;
  int a[N];
  for(int i=0; i<N; i++)
    a[i] = i;
  __m512i avec = _mm512_load_si512(a);
  __m512i idx = _mm512_setr_epi32(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  avec = _mm512_permutexvar_epi32(idx, avec);
  _mm512_store_si512(a, avec);
  for(int i=0; i<N; i++)
    printf("%d %d\n",i,a[i]);
}
