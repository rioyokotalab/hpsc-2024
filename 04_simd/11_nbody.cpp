#include <cstdio>
#include <cstdlib>
#include <cmath>
#include<x86intrin.h>

#define _mm512_square_ps(x) _mm512_mul_ps(x, x)
#define _mm512_cubic_ps(x) _mm512_mul_ps(x, _mm512_mul_ps(x, x))
#define _mm512_neg_ps(x) _mm512_sub_ps(_mm512_set1_ps(0),x)

int main() {
  const int N = 8;
  float x[N], y[N], m[N], fx[N], fy[N];
  int j[N];
  for(int i=0; i<N; i++) {
    x[i] = drand48();
    y[i] = drand48();
    m[i] = drand48();
    fx[i] = fy[i] = 0;
    j[i]=i;
  }
  __m512 xvec=_mm512_load_ps(x);
  __m512 yvec = _mm512_load_ps(y);
  __m512 mvec = _mm512_load_ps(m);
  __m512i jvec=_mm512_load_epi32(j);
  for(int i=0; i<N; i++) {
    /*for(int j=0; j<N; j++) {
      if(i != j) {
        float rx = x[i] - x[j];
        float ry = y[i] - y[j];
        float r = std::sqrt(rx * rx + ry * ry);
        fx[i] -= rx * m[j] / (r * r * r);
        fy[i] -= ry * m[j] / (r * r * r);
      }
    }*/
    __mmask16 mask = _mm512_cmp_epi32_mask(_mm512_set1_epi32(i), jvec, _MM_CMPINT_NE);
    __m512 rxvec = _mm512_sub_ps(_mm512_set1_ps(x[i]), xvec);
    __m512 ryvec = _mm512_sub_ps(_mm512_set1_ps(y[i]), yvec);
    __m512 rrvec = _mm512_setzero_ps();
    rrvec = _mm512_mask_blend_ps(mask, rrvec, _mm512_rsqrt14_ps(_mm512_add_ps(_mm512_square_ps(rxvec),
                                                                              _mm512_square_ps(ryvec))));
    __m512 tmp = _mm512_mul_ps(mvec, _mm512_cubic_ps(rrvec));
    __m512 tmpx = _mm512_neg_ps(_mm512_mul_ps(rxvec, tmp));
    __m512 tmpy = _mm512_neg_ps(_mm512_mul_ps(ryvec, tmp));
    fx[i] = _mm512_reduce_add_ps(tmpx);
    fy[i] = _mm512_reduce_add_ps(tmpy);
    printf("%d %g %g\n", i, fx[i], fy[i]);
  }
}
