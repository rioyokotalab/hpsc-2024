#include <cstdio>
#include <cmath>
#include <x86intrin.h>

int main() {
  const int N = 16;
  float x[N], y[N];
  for(int i=0; i<N; i++)
    x[i] = i * M_PI / (N - 1);
  __m512 xvec = _mm512_load_ps(x);
  xvec = _mm512_sin_ps(xvec);
  _mm512_store_ps(y, xvec);
  for(int i=0; i<N; i++)
    printf("%g %g\n",x[i],y[i]);
}
