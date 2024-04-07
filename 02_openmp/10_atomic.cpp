#include <cstdio>

int main() {
  float x[10];
  for (int i=0; i<10; i++)
    x[i] = 0.0;
#pragma omp parallel for
  for (int i=0; i<1000; i++) {
#pragma omp atomic update
    x[i%10]++;
  }
  for (int i=0; i<10; i++)
    printf("%d %g\n",i,x[i]);
}
