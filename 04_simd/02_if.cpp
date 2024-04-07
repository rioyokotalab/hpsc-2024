#include <cstdio>

int main() {
  const int N = 8;
  float a[N], b[N];
  for(int i=0; i<N; i++) {
    a[i] = i;
    b[i] = 0;
  }
  for(int i=0; i<N; i++) {
    if(a[i] > 3)
      b[i] = a[i];
  }
  for(int i=0; i<N; i++)
    printf("%d %g\n",i,b[i]);
}
