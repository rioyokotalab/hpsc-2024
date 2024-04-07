#include <cstdio>

int main() {
  const int N = 8;
  int idx[N] = {3,7,0,6,2,5,1,4};
  float a[N], b[N];
  for(int i=0; i<N; i++)
    a[idx[i]] = i * 0.1;
  for(int i=0; i<N; i++)
    b[i] = a[idx[i]];
  for(int i=0; i<N; i++)
    printf("%d %3.1f %3.1f\n",i,a[i],b[i]);
}
