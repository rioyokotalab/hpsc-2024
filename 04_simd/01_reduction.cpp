#include <cstdio>

int main() {
  const int N = 8;
  float a[N], b = 0;
  for(int i=0; i<N; i++)
    a[i] = 1;
  for(int i=0; i<N; i++)
    b += a[i];
  printf("%g\n",b);
}
