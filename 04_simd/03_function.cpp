#include <cstdio>

void add(float a, float b, float &c) {
  c = a + b;
}

int main() {
  const int N = 8;
  float a[N], b[N], c[N];
  for(int i=0; i<N; i++) {
    a[i] = i;
    b[i] = i * 0.1;
    c[i] = 0;
  }
  for(int i=0; i<N; i++)
    add(a[i],b[i],c[i]);
  for(int i=0; i<N; i++)
    printf("%d %g\n",i,c[i]);
}
