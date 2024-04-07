#include <cstdio>
#include <cmath>

int main() {
  const int N = 8;
  float x[N], y[N];
  for(int i=0; i<N; i++)
    x[i] = i * M_PI / (N - 1);
  for(int i=0; i<N; i++)
    y[i] = sin(x[i]);
  for(int i=0; i<N; i++)
    printf("%g %g\n",x[i],y[i]);
}
